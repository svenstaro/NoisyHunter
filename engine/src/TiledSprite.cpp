#include "TiledSprite.hpp"


#include <SFML/Graphics/Sprite.hpp>
#include <SFML/Graphics/Image.hpp>
//#include <SFML/Graphics/GraphicsContext.hpp> // ?? why not ??

namespace Engine{

using namespace sf;

// constructors
TiledSprite::TiledSprite() : Sprite() {}
TiledSprite::TiledSprite(const Image& Img, const Vector2f& Position, const Vector2f& Scale, float Rotation, const Color& Col) :
    Sprite(Img, Position, Scale, Rotation, Col){}


// RENDER TILED SPRITE


void TiledSprite::Render(RenderTarget&) const  {

    const Image* image = GetImage();
    const IntRect& sub_rect = GetSubRect();

    // Get the sprite size
    float Width  = static_cast<float>(sub_rect.GetWidth());
    float Height = static_cast<float>(sub_rect.GetHeight());
    float subw = sub_rect.GetWidth() / GetScale().x / 3;
    float subh = sub_rect.GetHeight() / GetScale().y / 3;

    // Check if the image is valid
    if (image && (image->GetWidth() > 0) && (image->GetHeight() > 0)){
        // Use the "offset trick" to get pixel-perfect rendering
        // see http://www.opengl.org/resources/faq/technical/transformations.htm#tran0030
        glTranslatef(0.375f, 0.375f, 0.f);



        // Bind the texture
        image->Bind();


        // 9 subrects
        for (int x = 0; x < 3; x++){
            for (int y = 0; y < 3; y++){
                // Calculate the texture coordinates

                FloatRect TexCoords = image->GetTexCoords(IntRect(sub_rect.Left + x     * Width / 3,
                                                                  sub_rect.Top  + y     * Height / 3,
                                                                  sub_rect.Left + (x+1) * Width / 3,
                                                                  sub_rect.Top  + (y+1) * Height / 3));

                /*FloatRect Rect(myIsFlippedX ? TexCoords.Right  : TexCoords.Left,
                               myIsFlippedY ? TexCoords.Bottom : TexCoords.Top,
                               myIsFlippedX ? TexCoords.Left   : TexCoords.Right,
                               myIsFlippedY ? TexCoords.Top    : TexCoords.Bottom);
*/

                FloatRect Rect(TexCoords.Left,TexCoords.Top,TexCoords.Right,TexCoords.Bottom);

                int left = 0;
                int right = subw / 3;
                int top = 0;
                int bottom = subh / 3;

                if (x == 1){
                    left = subw / 3;
                    right = Width - subw / 3;
                }
                if (x == 2) {
                    left = Width - subw / 3;
                    right = Width;
                }
                if (y == 1){
                    top = subh / 3;
                    bottom = Height - subh / 3;
                }
                if (y == 2) {
                    top = Height - subh / 3;
                    bottom = Height;
                }

                // Draw the tile's triangles
                glBegin(GL_QUADS);
                glTexCoord2f(Rect.Left,  Rect.Top);    glVertex2f(left, top);
                glTexCoord2f(Rect.Left,  Rect.Bottom); glVertex2f(left, bottom);
                glTexCoord2f(Rect.Right, Rect.Bottom); glVertex2f(right, bottom);
                glTexCoord2f(Rect.Right, Rect.Top);    glVertex2f(right, top);
                glEnd();
            }
        }
    } else {
        // Disable texturing
        glDisable(GL_TEXTURE_2D);

        // Draw the sprite's triangles
        glBegin(GL_QUADS);
        glVertex2f(0,     0);
        glVertex2f(0,     Height);
        glVertex2f(Width, Height);
        glVertex2f(Width, 0);
        glEnd();
    }
}

}
