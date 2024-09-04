#include "munkki2.hpp"
#include "../console.hpp"


munkki2::munkki2()
{
    ball = new Mesh();
//    ball->buildSphere(1.0f, 16, 16, Vector(1, 1, 1));

    ball->buildTorus(2, 1.0f, 32, 32);
    ball->calculateNormals();

//    ball->scale(1.7f);
}

munkki2::~munkki2()
{
    delete ball;
}
void munkki2::setTexture(Texture *text)
{
    texture = text;
}

void munkki2::draw(float time)
{
    if (!isActive(time))
        return;

    int i;

    glLoadIdentity();
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    const float movement = powf(sinf((1-calcPosFloat(framePosition, 0.0f, 0.1f))*3.141592f*0.5f), 3);
    const float movement2 = powf(sinf((calcPosFloat(framePosition, 0.9f, 1.0f))*3.141592f*0.5f), 3);
    glTranslatef((movement-movement2)*10, 0, -11);
    glRotatef(50+framePosition*360, 0.3f, 0.7f, 0.9f);

    glDisable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE);
    glColor4f(1,1,1,1);
    glEnable(GL_POINT_SMOOTH);
    glHint(GL_POINT_SMOOTH_HINT, GL_NICEST);


    int vcount = ball->getVertexCount();
    Vertex *vbuf = ball->getVertices();

    int fcount = ball->getFaceCount();
    Face *faces = ball->getFaces();

    glBindTexture(GL_TEXTURE_2D, texture->getID());

    glEnable(GL_TEXTURE_2D);
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glEnable(GL_TEXTURE_GEN_S);
	glEnable(GL_TEXTURE_GEN_T);

    glEnable(GL_DEPTH_TEST);

    glPushMatrix();



    glBegin(GL_TRIANGLES);
    for (i=0;i<fcount;i++)
    {
        Vertex *v1 = &vbuf[faces[i].v1];
        Vertex *v2 = &vbuf[faces[i].v2];
        Vertex *v3 = &vbuf[faces[i].v3];

        glNormal3fv((float *)&faces[i].normal);
//        glNormal3fv((float *)&v1->normal);
        glVertex3fv((float *)&v1->position);
//        glNormal3fv((float *)&v2->normal);
        glVertex3fv((float *)&v2->position);
//        glNormal3fv((float *)&v3->normal);
        glVertex3fv((float *)&v3->position);
    }
    glEnd();

    glPopMatrix();
	glDisable(GL_TEXTURE_GEN_S);
	glDisable(GL_TEXTURE_GEN_T);

/*
	glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	glTexGeni(GL_T, GL_TEXTURE_GEN_MODE, GL_SPHERE_MAP);
	myEnable(MY_TEXTURE_GEN_S);
	myEnable(MY_TEXTURE_GEN_T);
*/
}

bool munkki2::init(float start, float end)
{
    this->starttime = start;
    this->endtime = end;
    return true;
}

bool munkki2::free()
{
    return true;
}