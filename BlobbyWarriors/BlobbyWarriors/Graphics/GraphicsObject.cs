using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace BlobbyWarriors.Graphics
{
    public class GraphicsObject
    {
        public IList<Texture> Textures
        {
            get { return this.textures; }
        }

        public Texture ActiveTexture
        {
            get
            {
                if (this.activeTextureIndex < 0 || this.activeTextureIndex >= this.textures.Count)
                {
                    return null;
                }
                return this.textures[this.activeTextureIndex];
            }
        }

        private IList<Texture> textures;
        private int activeTextureIndex;

        public GraphicsObject()
        {
            this.textures = new List<Texture>();
            this.activeTextureIndex = -1;
        }
    }
}
