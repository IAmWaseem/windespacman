using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Drawing;

namespace SteeringCS
{
        class World
        {
            public Size ClientSize {get;set;}
            public Random random = new Random();
            public bool mirrored = false;

            //  private attributes  //

            public Vehicle target;
            public List<Vehicle> agents;
            long elapsedTime = 0;
            int numberOfVehicles = 10;

            //  singleton pattern   //
            private static World instance;

            private World()
            {
            }

            //  public methos   //
            public static World Instance
            {
                get
                {
                    if (instance == null)
                    {
                        instance = new World();
                        instance.Init("None");
                    }
                    return instance;
                }
            }

            public void Init(string steeringName)
            {
                ClientSize = new Size(1200, 600);

                if (steeringName.Equals("Seek", StringComparison.OrdinalIgnoreCase))
                {
                    DemoSeek();
                    return;
                }

                if (steeringName.Equals("Arrive", StringComparison.OrdinalIgnoreCase))
                {
                    DemoArrive();
                    return;
                }

                if (steeringName.Equals("Flee", StringComparison.OrdinalIgnoreCase))
                {
                    DemoFlee();
                    return;
                }

                if (steeringName.Equals("Wander", StringComparison.OrdinalIgnoreCase))
                {
                    DemoWander();
                    return;
                }

                if (steeringName.Equals("Explore", StringComparison.OrdinalIgnoreCase))
                {
                    DemoExplore();
                    return;
                }

                if (steeringName.Equals("Leader Following", StringComparison.OrdinalIgnoreCase))
                {
                    DemoLeaderFollowing();
                    return;
                }
                if (steeringName.Equals("Flocking", StringComparison.OrdinalIgnoreCase))
                {
                    DemoFlocking();
                    return;
                }


                //   default behavior:
                DemoNone();

            }

            private void DemoNone()
            {
                target = new Vehicle(null, Vehicle.SB.None);
                target.MaxSpeed = 0;
                target.CurrentPosition = new Vector2D(ClientSize.Width / 2, ClientSize.Height / 2);

                agents = new List<Vehicle>();
                agents.Add(target);    //  target of "none"

                for (int i = 1; i < numberOfVehicles; i++)
                {
                    agents.Add(new Vehicle(target, Vehicle.SB.None));
                }
            }
            
            private void DemoSeek()
            {
                target = new Vehicle(null, Vehicle.SB.None);
                target.MaxSpeed = 0;
                target.CurrentPosition = new Vector2D(ClientSize.Width / 2, ClientSize.Height / 2);

                agents = new List<Vehicle>();
                agents.Add(target);    //  target of seek

                for (int i = 1; i < numberOfVehicles; i++)
                {
                    agents.Add(new Vehicle(target, Vehicle.SB.Seek));
                }
            }

            private void DemoArrive()
            {
                target = new Vehicle(null, Vehicle.SB.None);
                target.MaxSpeed = 0;
                target.CurrentPosition = new Vector2D(ClientSize.Width / 2, ClientSize.Height / 2);

                agents = new List<Vehicle>();
                agents.Add(target);    //  target of arrive

                for (int i = 1; i < numberOfVehicles; i++)
                {
                    agents.Add(new Vehicle(target, Vehicle.SB.Arrive));
                }
            }

            private void DemoFlee()
            {
                target = new Vehicle(null, Vehicle.SB.None);
                target.MaxSpeed = 0;
                target.CurrentPosition = new Vector2D(ClientSize.Width / 2, ClientSize.Height / 2);

                agents = new List<Vehicle>();
                agents.Add(target);    //  target of flee

                for (int i = 1; i < numberOfVehicles; i++)
                {
                    agents.Add(new Vehicle(target, Vehicle.SB.Flee));
                }
            }

            private void DemoWander()
            {
                target = new Vehicle(null, Vehicle.SB.Wander);
                target.MaxSpeed = 2;
                target.CurrentPosition = new Vector2D(ClientSize.Width / 2, ClientSize.Height / 2);

                agents = new List<Vehicle>();
                agents.Add(target);    //  leader

                for (int i = 1; i < numberOfVehicles; i++)
                {
                    agents.Add(new Vehicle(agents[i - 1], Vehicle.SB.Arrive));
                }
            }

            private void DemoLeaderFollowing()
            {
                target = new Vehicle(null, Vehicle.SB.Wander);
                target.MaxSpeed = 2;
                target.CurrentPosition = new Vector2D(ClientSize.Width / 2, ClientSize.Height / 2);

                agents = new List<Vehicle>();
                agents.Add(target);    //  leader

                for (int i = 1; i < numberOfVehicles; i++)
                {
                    agents.Add(new Vehicle(target, Vehicle.SB.LeaderFollowing));
                }
            }

            private void DemoFlocking()
            {
                target = new Vehicle(null, Vehicle.SB.Wander);
                target.MaxSpeed = 2;
                target.CurrentPosition = new Vector2D(ClientSize.Width / 2, ClientSize.Height / 2);

                agents = new List<Vehicle>();
                //agents.Add(target);    //  leader

                for (int i = 1; i < numberOfVehicles*6; i++)
                {
                    agents.Add(new Vehicle(null, Vehicle.SB.Flocking));
                }
            }

            private void DemoExplore()
            {
                target = new Vehicle(null, Vehicle.SB.Explore);
                target.MaxSpeed = 5;
                target.CurrentPosition = new Vector2D(25, 0);

                agents = new List<Vehicle>();
                agents.Add(target);    //  target of seek
            }


            public void Update(long elapsedTime)
            {
                this.elapsedTime = elapsedTime;

                foreach (Vehicle agent in agents)
                {
                    agent.Update();
                }
            }

            public void Render(Graphics g)
            {
                g.Clear(Color.Black);
                foreach (Vehicle agent in agents)
                    agent.Render(g);
            }
    }

}
