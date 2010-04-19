using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace SteeringCS
{
    class Vehicle
    {
        public enum SB
        {
            None,
            Seek,
            Arrive,
            Flee,
            Wander,
            Pursuit,
            Evade,
            ObstacleAvoidance,
            WallAvoidance,
            Interpose,
            Hide,
            PathFollowing,
            OffsetPursuit,
            Cohesion,
            Alignment,
            Separation,
            Flocking,
            Explore,
            LeaderFollowing
        }

        private float mass;
        private int max_speed;
        private int max_force;

        public Vector2D CurrentPosition;
        private Vector2D velocity;
        private Vector2D acceleration;
        private Vector2D heading;
        private Vector2D steerForce;
        private Vehicle target;
        private SB sb;

        private Brush brushVehicle;
        private Brush brushTarget;
        private Pen whitePen;

        //wander specific variables
        private Vector2D wanderTarget = new Vector2D(0);
        private float wandertheta = 0.5f;


        public Vehicle(Vehicle target, SB sb)
        {
            this.sb = sb;
            mass = World.Instance.random.Next(20, 80);
            max_force = 20;
            max_speed = 10;
            velocity = new Vector2D(5, 5);
            acceleration = Vector2D.None();
            heading = Vector2D.Normalize(velocity);
            CurrentPosition = new Vector2D(World.Instance.random.Next(World.Instance.ClientSize.Width), World.Instance.random.Next(World.Instance.ClientSize.Height));
            steerForce = Vector2D.None();
            brushVehicle = Brushes.Red;
            brushTarget = Brushes.Blue;
            whitePen = Pens.White;
            this.target = target;
        }

        #region Properties
        public Vector2D Velocity
        {
            get
            {
                return velocity;
            }
        }

        public int MaxForce
        {
            get { return max_force; }
            set { max_force = value; }
        }

        public int MaxSpeed
        {
            get { return max_speed; }
            set { max_speed = value; }
        }

        public float Mass
        {
            get { return mass; }
            set { mass = value; }
        }

        public SB SteeringBehavior
        {
            get { return sb; }
            set { sb = value; }
        }
        #endregion

        public void Update()
        {
            heading = Vector2D.Normalize(velocity);

            //  compute steerforce
            steerForce = Vector2D.None();

            switch (sb)
            {
                case SB.None:
                    break;
                case SB.Seek:
                    if (target != null)
                        steerForce = SteeringBehaviours.Seek(target.CurrentPosition, ref CurrentPosition, ref velocity, max_speed);
                    break;
                case SB.Arrive:
                    if (target != null)
                        steerForce = SteeringBehaviours.Arrive(target.CurrentPosition, ref CurrentPosition, ref velocity, max_speed);
                    break;
                case SB.Flee:
                    if (target != null)
                        steerForce = SteeringBehaviours.Flee(target.CurrentPosition, ref CurrentPosition, ref velocity, max_speed);
                    break;
                case SB.Wander:
                    steerForce = SteeringBehaviours.Wander(ref wanderTarget, ref CurrentPosition, ref velocity, ref heading, ref wandertheta, max_speed);
                    break;
                case SB.Explore:
                    steerForce = SteeringBehaviours.Explore(ref wanderTarget, ref CurrentPosition, ref velocity, 20);
                    break;
                case SB.LeaderFollowing:
                    steerForce = SteeringBehaviours.LeaderFollowing(ref heading, target.CurrentPosition, ref CurrentPosition, ref velocity, max_speed, max_force);
                    break;
                case SB.Flocking:
                    steerForce = SteeringBehaviours.Flocking(ref velocity, max_speed, ref CurrentPosition, max_force);
                    break;
            }

            //  compute new current position
            steerForce = Vector2D.Truncate(steerForce, max_force);
            acceleration = steerForce / mass;
            velocity = Vector2D.Truncate(velocity + acceleration, max_speed);
            heading = Vector2D.Normalize(velocity);

            //  prevent kind of jitter
            //float treshold = 0.099f;
            //Vector2D newPosition = Vector2D.Add(velocity, CurrentPosition);
            //if (Math.Abs(newPosition.X - CurrentPosition.X) < treshold
            //    && Math.Abs(newPosition.Y - CurrentPosition.Y) < treshold)
            //    return;     //  keep current position

            CurrentPosition = Vector2D.Add(velocity, CurrentPosition);

            //

            if (!World.Instance.mirrored)
            {
                if (CurrentPosition.X > World.Instance.ClientSize.Width)
                    CurrentPosition.X = 0;
                if (CurrentPosition.Y > World.Instance.ClientSize.Height)
                    CurrentPosition.Y = 0;
                if (CurrentPosition.X < 0)
                    CurrentPosition.X = World.Instance.ClientSize.Width;
                if (CurrentPosition.Y < 0)
                    CurrentPosition.Y = World.Instance.ClientSize.Height;
            }
            else
            {
                if (CurrentPosition.X > World.Instance.ClientSize.Width)
                    velocity.X *= -1;
                if (CurrentPosition.Y > World.Instance.ClientSize.Height)
                    velocity.Y *= -1;
                if (CurrentPosition.X < 0)
                    velocity.X *= -1;
                if (CurrentPosition.Y < 0)
                    velocity.Y *= -1;
            }
        }
        private static int fpsCount = 0;
        public void Render(Graphics g)
        {
            if (sb == SB.Explore)
            {
                PointF[] points = SteeringBehaviours.BeenPoints();
                if (points.Length > 1)
                    g.DrawLines(new Pen(Brushes.GreenYellow, 1f), points);
            }

            if (max_speed != 0)
            {
                PointF top = new PointF(heading.X * 30 + CurrentPosition.X, heading.Y * 30 + CurrentPosition.Y);
                PointF left = new PointF(heading.Y * (-10) + CurrentPosition.X, heading.X * 10 + CurrentPosition.Y);
                PointF right = new PointF(heading.Y * 10 + CurrentPosition.X, heading.X * (-10) + CurrentPosition.Y);

                g.DrawLine(whitePen, top, left);
                g.DrawLine(whitePen, top, right);
                g.DrawLine(whitePen, right, left);
                g.FillPolygon(target==null?brushTarget:brushVehicle, new PointF[] { top, left, right });

                if (target != null)
                {
                    g.DrawLine(whitePen, CurrentPosition.ToPointF(), target.CurrentPosition.ToPointF());
                }
            }
            else
            {
                g.FillEllipse(brushTarget, CurrentPosition.X - 10, CurrentPosition.Y - 10, 20, 20);
                int arriveRadius = 100;
                g.DrawEllipse(Pens.SkyBlue, new RectangleF(new PointF(CurrentPosition.X - arriveRadius, CurrentPosition.Y - arriveRadius), new SizeF(arriveRadius * 2, arriveRadius * 2)));
            }

            if (sb == SB.Wander || sb == SB.Explore)
            {
                g.DrawEllipse(Pens.SkyBlue, new RectangleF(new PointF(wanderTarget.X - 80, wanderTarget.Y - 80), new SizeF(80 * 2, 80 * 2)));
                g.FillEllipse(Brushes.Yellow, new RectangleF(new PointF(wanderTarget.X - 5, wanderTarget.Y - 5), new SizeF(5 * 2, 5 * 2)));
            }

            

            bool debug = false;
            if (debug)
            {
                //if (fpsCount >= 20)
                //{
                    Font font = new Font("Courier New", 12);
                    Brush brushDebug = Brushes.White;
                    g.DrawString("Position       " + this.CurrentPosition.ToString(), font, brushDebug, 10, 30);
                    g.DrawString("Velocity       " + this.velocity.ToString(), font, brushDebug, 10, 50);
                    g.DrawString("Acceleration   " + this.acceleration.ToString(), font, brushDebug, 10, 70);
                    g.DrawString("Heading        " + this.heading.ToString(), font, brushDebug, 10, 90);
                    g.DrawString("Steering Force " + this.steerForce.ToString(), font, brushDebug, 10, 110);
                    if (this.target != null)
                        g.DrawString("Target         " + this.target.CurrentPosition.ToString(), font, brushDebug, 10, 130);

                    g.DrawString("Speed " + velocity.Length().ToString(), font, brushDebug, 450, 50);
                //    fpsCount = 0;
                //}
                //else
                //    fpsCount = fpsCount + 1;
            }
        }
    }
}
