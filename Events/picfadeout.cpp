#include "picfadeout.hpp"

picfadeout::picfadeout()
{
}

picfadeout::~picfadeout()
{
}

void picfadeout::draw(float time)
{
    if (!isActive(time))
        return;

    float fadepos = 1;
    if (time > (endtime - fadetime))
    {
        fadepos = (endtime - time) / fadetime;
    }

    glLoadIdentity();
    perspective2D(1,1);

    glEnable(GL_TEXTURE_2D);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glColor4f(1,1,1,fadepos);

    glDisable(GL_DEPTH_TEST);
    glBindTexture(GL_TEXTURE_2D, texture->getID());
    glBegin(GL_QUADS);

    glTexCoord2f(0, 1);
    glVertex2f(0, 0);
    glTexCoord2f(1, 1);
    glVertex2f(1, 0);
    glTexCoord2f(1, 0);
    glVertex2f(1, 1);
    glTexCoord2f(0, 0);
    glVertex2f(0, 1);

    glEnd();

    perspective3D();
    glLoadIdentity();
    glDisable(GL_BLEND);

}
void picfadeout::setFadeTime(float fadetime)
{
    this->fadetime = fadetime;
}

void picfadeout::setTexture(Texture *text)
{
    texture = text;
}
bool picfadeout::init(float start, float end)
{
    this->starttime = start;
    this->endtime = end;

    return true;
}

bool picfadeout::free()
{
    return true;
}