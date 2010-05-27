using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using Microsoft.Xna.Framework.Graphics;
using Microsoft.Xna.Framework;
using System.Diagnostics;

namespace Karo.Gui
{
    public static class DrawBoundingBox
    {
        static BasicEffect effect;
        static VertexPositionColor[] verts;
        static VertexDeclaration decl;

        static void Init(GraphicsDevice device)
        {
            Debug.Assert(decl == null);

            effect = new BasicEffect(device, null);
            verts = new VertexPositionColor[24];

            for (int i = 0; i < verts.Length; i++)
            {
                verts[i].Color = Color.Yellow;
            }

            decl = new VertexDeclaration(device, VertexPositionColor.VertexElements);
        }

        public static void Draw(GraphicsDevice device, BoundingBox box, Matrix view, Matrix projection)
        {
            if (decl == null)
                Init(device);

            Vector3 min = box.Min;
            Vector3 max = box.Max;

            verts[0].Position = new Vector3(min.X, min.Y, min.Z);
            verts[1].Position = new Vector3(max.X, min.Y, min.Z);
            verts[2].Position = new Vector3(min.X, min.Y, max.Z);
            verts[3].Position = new Vector3(max.X, min.Y, max.Z);
            verts[4].Position = new Vector3(min.X, min.Y, min.Z);
            verts[5].Position = new Vector3(min.X, min.Y, max.Z);
            verts[6].Position = new Vector3(max.X, min.Y, min.Z);
            verts[7].Position = new Vector3(max.X, min.Y, max.Z);
            verts[8].Position = new Vector3(min.X, max.Y, min.Z);
            verts[9].Position = new Vector3(max.X, max.Y, min.Z);
            verts[10].Position = new Vector3(min.X, max.Y, max.Z);
            verts[11].Position = new Vector3(max.X, max.Y, max.Z);
            verts[12].Position = new Vector3(min.X, max.Y, min.Z);
            verts[13].Position = new Vector3(min.X, max.Y, max.Z);
            verts[14].Position = new Vector3(max.X, max.Y, min.Z);
            verts[15].Position = new Vector3(max.X, max.Y, max.Z);
            verts[16].Position = new Vector3(min.X, min.Y, min.Z);
            verts[17].Position = new Vector3(min.X, max.Y, min.Z);
            verts[18].Position = new Vector3(max.X, min.Y, min.Z);
            verts[19].Position = new Vector3(max.X, max.Y, min.Z);
            verts[20].Position = new Vector3(min.X, min.Y, max.Z);
            verts[21].Position = new Vector3(min.X, max.Y, max.Z);
            verts[22].Position = new Vector3(max.X, min.Y, max.Z);
            verts[23].Position = new Vector3(max.X, max.Y, max.Z);

            //effect.Parameters["worldViewProj"].SetValue(viewproj);
            effect.View = view;
            effect.Projection = projection;
            effect.Begin();

            EffectPass pass = effect.CurrentTechnique.Passes[0];

            pass.Begin();
            device.VertexDeclaration = decl;
            device.DrawUserPrimitives<VertexPositionColor>(PrimitiveType.LineList, verts, 0, 12);
            pass.End();

            effect.End();
        }
    }

}
