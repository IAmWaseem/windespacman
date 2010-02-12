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
    }
}
