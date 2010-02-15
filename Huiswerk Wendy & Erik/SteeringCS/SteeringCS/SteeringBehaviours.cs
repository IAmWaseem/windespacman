using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace SteeringCS
{
    /***
     * SEE: http://www.red3d.com/cwr/steer/gdc99/
     * */

    class SteeringBehaviours
    {
        /***
         *  The seek steering behavior returns a force that directs an agent toward a target position 
         * */
        public static Vector2D Seek(Vector2D targetPosition, ref Vector2D currentPosition, ref Vector2D Velocity, int max_speed)
        {
            Vector2D desired_V = Vector2D.Normalize(Vector2D.Subtract(targetPosition, currentPosition)) * max_speed;
            return Vector2D.Subtract(desired_V, Velocity);
        }
        /***
         * Seek is useful for getting an agent moving in the right direction, but often you'll want your agents
         * to come to a gentle halt at the target position, and as you've seen, seek is not too great at stopping gracefully.
         * Arrive is a behavior that steers the agent in such a way it decelerates onto the target position.
         * */
        public static Vector2D Arrive(Vector2D targetPosition, ref Vector2D currentPosition, ref Vector2D Velocity, int max_speed)
        {
            int arriveRadius = 100;

            Vector2D toTarget = Vector2D.Subtract(targetPosition, currentPosition);
            double distance = toTarget.Length();
            if (distance > 0)
            {
                double speed = max_speed * (distance / arriveRadius);
                speed = Math.Min(speed, max_speed);
                Vector2D desired_V = toTarget * (float)(speed / distance);
                return Vector2D.Subtract(desired_V, Velocity);
            }
            return Vector2D.None();
        }

        /***
         * Flee is the opposite of seek. Instead of producing a steering force to steer the agent toward a target position, flee creates a force that steers the agent away. 
         * */
        public static Vector2D Flee(Vector2D targetPosition, ref Vector2D currentPosition, ref Vector2D Velocity, int max_speed)
        {
            int FOV = 100;  //  Field Of View

            if (Vector2D.Length(Vector2D.Subtract(targetPosition, currentPosition)) > FOV)
            {
                return Vector2D.None();
            }
            else
            {
                Vector2D desired_V = Vector2D.Normalize(Vector2D.Subtract(currentPosition, targetPosition)) * max_speed;
                return Vector2D.Subtract(desired_V, Velocity);
            }
        }

        /***
         * You'll often find wander a useful ingredient when creating an agent's behavior.
         * It's designed to produce a steering force that will give the impression of a random walk through the agent's environment.
         * */
        public static Vector2D Wander(ref Vector2D wanderTarget, ref Vector2D currentPosition, ref Vector2D Velocity, ref Vector2D heading, ref float wandertheta, int max_speed)
        {
            //  see:    http://www.shiffman.net/teaching/nature/steering/
            float wanderR = 80.0f;         // Radius for our "wander circle"
            float wanderD = 40.0f;         // Distance for our "wander circle"
            float change = 0.5f;
            wandertheta += (float)(World.Instance.random.NextDouble() - World.Instance.random.NextDouble()) * change;     // Randomly change wander theta -1 .. +1

            // Now we have to calculate the new location to steer towards on the wander circle
            Vector2D circleloc = Velocity.Copy();   // Start with velocity
            circleloc.Normalize();                  // Normalize to get heading
            circleloc *= wanderD;                   // Multiply by distance
            circleloc += currentPosition;           // Make it relative to boid's location

            Vector2D circleOffSet = new Vector2D(wanderR * Math.Cos(wandertheta), wanderR * Math.Sin(wandertheta));
            Vector2D target = Vector2D.Add(circleloc, circleOffSet);

            wanderTarget = target;
            //  do a seek to target ...
            return Seek(target, ref currentPosition, ref Velocity, max_speed);
        }

        private static void RemoveAllTargetsInRange(float range, ref Vector2D currentPosition)
        {
            float beenRange = range;
            List<Vector2D> toKeep = new List<Vector2D>();

            if (HasBeen == null)
                HasBeen = new List<Vector2D>();
            if (ExploreGrid == null)
                ExploreGrid = new List<Vector2D>();

            
            foreach (Vector2D vec in ExploreGrid)
            {
                float diffX = vec.X - currentPosition.X;
                float diffY = vec.Y - currentPosition.Y;
                if ((diffX <= range && diffX > -1 * range)
                    && (diffY <= range && diffY > -1 * range))
                {
                    // do nothing                        
                }
                else
                    toKeep.Add(vec);
            }
            ExploreGrid.Clear();
            foreach (Vector2D vec in toKeep)
            {
                ExploreGrid.Add(vec);
            }
        }

        public static PointF[] BeenPoints()
        {
            if (HasBeen == null)
                HasBeen = new List<Vector2D>();
            PointF[] p = new PointF[HasBeen.Count];
            for (int i = 0; i < HasBeen.Count; i++)
            {
                p[i].X = HasBeen[i].X;
                p[i].Y = HasBeen[i].Y;
            }


            return p;
        }

        public static PointF[] ExplorePoints()
        {
            if (ExploreGrid == null)
                ExploreGrid = new List<Vector2D>();
            PointF[] p = new PointF[ExploreGrid.Count];
            for (int i = 0; i < ExploreGrid.Count; i++)
            {
                p[i].X = ExploreGrid[i].X;
                p[i].Y = ExploreGrid[i].Y;
            }

            return p;
        }

        private static List<Vector2D> HasBeen = null;
        private static List<Vector2D> ExploreGrid = null;
        /***
         * You'll often find wander a useful ingredient when creating an agent's behavior.
         * It's designed to produce a steering force that will give the impression of a random walk through the agent's environment.
         * */
        public static Vector2D Explore(ref Vector2D wanderTarget, ref Vector2D currentPosition, ref Vector2D Velocity, int max_speed)
        {
            //  see:    http://www.shiffman.net/teaching/nature/steering/


            if (ExploreGrid == null)
            {
                ExploreGrid = new List<Vector2D>();
                HasBeen = new List<Vector2D>();

                int height = World.Instance.ClientSize.Height;
                int width = World.Instance.ClientSize.Width;

                for (int x = 20; x < (width - 20); x++)
                {
                    for (int y = 20; y < (height - 20); y++)
                    {
                        ExploreGrid.Add(new Vector2D(x, y));
                    }
                }                
            }

            int arriveRadius = 100;
            Vector2D theTarget = new Vector2D(World.Instance.ClientSize.Width / 2, World.Instance.ClientSize.Height / 2);

            float diffX = 0;
            float diffY = 0;
            float distanceToTarget = 0;

            if (ExploreGrid.Count <= 0)
            {

            }
            else
            {
                diffX = ExploreGrid.First().X - currentPosition.X;
                diffY = ExploreGrid.First().Y - currentPosition.Y;
                distanceToTarget = 30f;
                RemoveAllTargetsInRange(distanceToTarget, ref currentPosition);

                
            }
            HasBeen.Add(currentPosition);

            if (ExploreGrid.Count <= 0)
            {
                theTarget = new Vector2D(World.Instance.ClientSize.Width / 2, World.Instance.ClientSize.Height / 2);
            }
            else
            {
                if ((diffX <= distanceToTarget && diffX > -1 * distanceToTarget)
                    && (diffY <= distanceToTarget && diffY > -1 * distanceToTarget))
                {
                    theTarget = new Vector2D(ExploreGrid.First().X, ExploreGrid.First().Y);
                }
                else
                {
                    theTarget = new Vector2D(ExploreGrid.First().X, ExploreGrid.First().Y);
                }
            }

            Vector2D toTarget = Vector2D.Subtract(theTarget, currentPosition);
            wanderTarget = theTarget;

            double distance = toTarget.Length();
            if (distance > 0)
            {
                //Arrive
                double speed = max_speed * (distance / arriveRadius);
                speed = Math.Min(speed, max_speed);
                Vector2D desired_V = toTarget * (float)(speed / distance);
                return Vector2D.Subtract(desired_V, Velocity);

                ////Seek
                //Vector2D desired_V = Vector2D.Normalize(Vector2D.Subtract(toTarget, currentPosition)) * max_speed;
                //return Vector2D.Subtract(desired_V, Velocity);
            }
            return Vector2D.None();
        }
        public static void ResetLists()
        {
            ExploreGrid = null;
            HasBeen = null;
        }

        public static Vector2D LeaderFollowing(ref Vector2D heading, Vector2D targetPosition, ref Vector2D currentPosition, ref Vector2D Velocity, int max_speed, int max_force)
        {
            // Separate
            Vector2D s = Separate(World.Instance.agents, ref currentPosition, ref Velocity, max_speed);
            //Arrival

            Vector2D behindLeader = Vector2D.Subtract(targetPosition, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);
            behindLeader = Vector2D.Subtract(behindLeader, heading);


            Vector2D a = Arrive(behindLeader, ref currentPosition, ref Velocity, max_speed);
            
            // combineren
            Vector2D total = new Vector2D();
            total.X = (a.X * 2) + (s.X * 1);
            total.Y = (a.Y * 2) + (s.Y * 1);
            total = Vector2D.Truncate(total, max_force);

            return total;
        }
        public static Vector2D Separate(List<Vehicle> vehicles, ref Vector2D vehicle1, ref Vector2D Velocity, int max_speed)
        {
            int r = 45;
            float desiredseparation = r * 2;
            Vector2D steer = new Vector2D();
            int count = 0;
            // For every boid in the system, check if it's too close
            for (int i = 0; i < vehicles.Count; i++)
            {
                Vehicle vehicle2 = vehicles[i];

                Vector2D diff = Vector2D.Subtract(vehicle1, vehicle2.CurrentPosition);
                // If the distance is greater than 0 and less than an arbitrary amount (0 when you are yourself)
                if ((diff.X > 0 || diff.Y > 0) && (diff.X < desiredseparation || diff.Y < desiredseparation))
                {
                    // Calculate vector pointing away from neighbor
                    diff.Normalize();
                    steer = Vector2D.Add(steer, diff);
                    count++;            // Keep track of how many
                }
            }
            // Average -- divide by how many
            if (count > 0)
            {
                float X = steer.X / count;
                float Y = steer.Y / count;
                steer.X = X;
                steer.Y = Y;
            }

            // As long as the vector is greater than 0
            if (steer.X > 0 || steer.Y > 0)
            {
                // Implement Reynolds: Steering = Desired - Velocity
                steer.Normalize();
                float x = steer.X * max_speed;
                float y = steer.Y * max_speed;
                steer.X = x;
                steer.Y = y;
                steer = Vector2D.Subtract(steer, Velocity);
            }
            return steer;
        }
    }
}
