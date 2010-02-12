using System;
using System.Collections.Generic;
using System.Text;
using System.Drawing;

namespace SteeringCS
{
    /***
     * implementation of a 2-D vector
     * */

    public struct Vector2D
    {
        public float X, Y;

        public Vector2D(float a)
        {
            X = a;
            Y = a;
        }

        public Vector2D(float a, float b)
        {
            X = a;
            Y = b;
        }

        public Vector2D(double a, double b)
        {
            X = (float)a;
            Y = (float)b;
        }

        public Vector2D(PointF input)
        {
            X = input.X;
            Y = input.Y;
        }

        public Vector2D Copy()
        {
            return new Vector2D(X, Y);
        }

        public double Length()
        {
            return Math.Sqrt(X * X + Y * Y);
        }

        
        public static Vector2D None()
        {
            return new Vector2D(0);
        }

        public static double Length(Vector2D v1)
        {
            return Math.Sqrt(v1.X * v1.X + v1.Y * v1.Y);
        }

        public static Vector2D Normalize(Vector2D v1)
        {
            double length = Vector2D.Length(v1);
            if (length > 0)
            {
                return new Vector2D((float)(v1.X / Vector2D.Length(v1)), (float)(v1.Y / Vector2D.Length(v1)));
            }
            else
            {
                return new Vector2D((float)(v1.X / 1), (float)(v1.Y / 1));
            }
        }

        public void Normalize()
        {
            this.X = (float)(this.X / Vector2D.Length(this));
            this.Y = (float)(this.Y / Vector2D.Length(this));
        }

        public static Vector2D Add(Vector2D v1, Vector2D v2)
        {
            return new Vector2D(v1.X + v2.X, v1.Y + v2.Y);
        }

        public static Vector2D Subtract(Vector2D v1, Vector2D v2)
        {
            return new Vector2D(v1.X - v2.X, v1.Y - v2.Y);
        }

        public static float Dot(Vector2D v1, Vector2D v2)
        {
            return (v1.X * v2.X + v1.Y * v2.Y);
        }

        public static Vector2D Multiply(Vector2D v1, float v2)
        {
            return new Vector2D(v1.X * v2, v1.Y * v2);
        }

        public static Vector2D operator +(Vector2D v1, int a)
        {
            return new Vector2D(v1.X + a, v1.Y + a);
        }

        public static Vector2D operator +(Vector2D v1, Vector2D a)
        {
            return new Vector2D(v1.X + a.X, v1.Y + a.Y);
        }

        public static Vector2D operator *(Vector2D v1, int a)
        {
            return new Vector2D(v1.X * a, v1.Y * a);
        }

        public static Vector2D operator *(Vector2D v1, float a)
        {
            return new Vector2D(v1.X * a, v1.Y * a);
        }

        public static Vector2D operator /(Vector2D v1, int a)
        {
            if (a != 0)
            {
                return new Vector2D(v1.X / a, v1.Y / a);
            }
            else
                return v1;
        }

        public static Vector2D operator /(Vector2D v1, float a)
        {
            if (a != 0)
                return new Vector2D(v1.X / a, v1.Y / a);
            else
                return v1;
        }

        public static Vector2D operator /(Vector2D v1, double a)
        {
            if (a != 0)
                return new Vector2D((float)(v1.X / a), (float)(v1.Y / a));
            else
                return v1;
        }

        public override string ToString()
        {
            return (X.ToString() + ", " + Y.ToString());
        }

        public PointF ToPointF()
        {
            return new PointF(X, Y);
        }

        internal static Vector2D Truncate(Vector2D vec, float max_value)
        {
            if (vec.Length() > max_value)
            {
                return Vector2D.Multiply(Vector2D.Normalize(vec), max_value);
            }
            return vec;
        }
    }
}
