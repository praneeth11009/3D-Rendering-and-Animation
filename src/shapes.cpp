#include "shapes.hpp"
#include <math.h>

extern float size;
glm::vec4 skincolor1 = glm::vec4(1.0,227.0/255,159.0/255,1.0);
glm::vec4 colors1[12] = {
    glm::vec4(0.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 0.0, 0.0, 1.0),
    glm::vec4(1.0, 1.0, 0.0, 1.0),
    glm::vec4(0.0, 1.0, 0.0, 1.0),
    glm::vec4(0.0, 0.0, 1.0, 1.0),
    glm::vec4(1.0, 0.0, 1.0, 1.0),
    glm::vec4(1.0, 1.0, 1.0, 1.0),
    glm::vec4(0.0, 1.0, 1.0, 1.0),
    glm::vec4(0.0, 0.0, 1.0, 1.0),
    glm::vec4(1.0, 0.0, 1.0, 1.0),
    glm::vec4(1.0, 1.0, 1.0, 1.0),
    glm::vec4(0.0, 1.0, 1.0, 1.0)
};

//! for quadrilateral using 2 triangles
void quad(glm::vec4* v_positions,glm::vec4* v_colors,glm::vec4* positions,int* tri_idx,int a, int b, int c, int d)
{
    v_colors[*tri_idx] = colors1[a]; v_positions[*tri_idx] = positions[a]; *tri_idx = *tri_idx + 1;
    v_colors[*tri_idx] = colors1[b]; v_positions[*tri_idx] = positions[b]; *tri_idx = *tri_idx + 1;
    v_colors[*tri_idx] = colors1[c]; v_positions[*tri_idx] = positions[c]; *tri_idx = *tri_idx + 1;
    v_colors[*tri_idx] = colors1[a]; v_positions[*tri_idx] = positions[a]; *tri_idx = *tri_idx + 1;
    v_colors[*tri_idx] = colors1[c]; v_positions[*tri_idx] = positions[c]; *tri_idx = *tri_idx + 1;
    v_colors[*tri_idx] = colors1[d]; v_positions[*tri_idx] = positions[d]; *tri_idx = *tri_idx + 1;
}

//! quadrilateral frustum with shear option in height direction
csX75::HNode* cuboid(float lx0,float hy0,float bz0,float hy10,float bz10,glm::vec4 offset,float shear0,csX75::HNode* parent,glm::vec4 color1,glm::vec4 color2)
{
	const int num_vertices = 36;
	glm::vec4 v_positions[num_vertices];
	glm::vec4 v_colors[num_vertices];

	int tri_idx=0;
    float lx = lx0*size;
    float hy = hy0*size;float hy1 = hy10*size;
    float bz = bz0*size;float bz1 = bz10*size;
    float shear = shear0*size;
    glm::vec4 positions[8];

    positions[0] = glm::vec4(-lx/2,-hy/2,bz/2,1.0);   colors1[0] = color1;
    positions[1] = glm::vec4(-lx/2,hy/2,bz/2,1.0);    colors1[1] = color1;
    positions[2] = glm::vec4(lx/2,(hy1/2)+shear,bz1/2,1.0);   colors1[2] = color2;
    positions[3] = glm::vec4(lx/2,(-hy1/2)+shear,bz1/2,1.0);  colors1[3] = color2;
    positions[4] = glm::vec4(-lx/2,-hy/2,-bz/2,1.0);  colors1[4] = color1;
    positions[5] = glm::vec4(-lx/2,hy/2,-bz/2,1.0);   colors1[5] = color1;
    positions[6] = glm::vec4(lx/2,(hy1/2)+shear,-bz1/2,1.0);  colors1[6] = color2;
    positions[7] = glm::vec4(lx/2,(-hy1/2)+shear,-bz1/2,1.0); colors1[7] = color2;

    for(int i=0;i<8;i++)
    {
    	positions[i].x = positions[i].x + size*offset.x;
    	positions[i].y = positions[i].y + size*offset.y;
    	positions[i].z = positions[i].z + size*offset.z;
    }
    quad(v_positions,v_colors,positions,&tri_idx, 1, 0, 3, 2 );
    quad(v_positions,v_colors,positions,&tri_idx, 2, 3, 7, 6 );
    quad(v_positions,v_colors,positions,&tri_idx, 3, 0, 4, 7 );
    quad(v_positions,v_colors,positions,&tri_idx, 6, 5, 1, 2 );
    quad(v_positions,v_colors,positions,&tri_idx, 4, 5, 6, 7 );
    quad(v_positions,v_colors,positions,&tri_idx, 5, 4, 0, 1 );
    csX75::HNode* node = new csX75::HNode(parent,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
    return node;
}

//! Hybrid with elliptic cylindrical surface on one half and half of hexagonal frustum on other half (used for animal face)
csX75::HNode* cuboid2(float a10,float b10,float a20,float b20,float h0,glm::vec4 offset,float shear0,csX75::HNode* parent,glm::vec4 color1,glm::vec4 color2)
{
    const int num_vertices = 12*180 + 12*3;
    glm::vec4 v_positions[num_vertices];
    glm::vec4 v_colors[num_vertices];
    int tri_idx = 0;
    float a1 = a10*size, b1 = b10*size;
    float a2 = a20*size, b2 = b20*size;
    float h = h0*size;
    float shear = shear0*size;

    offset.x *= size; offset.y *= size; offset.z *= size;
    glm::vec4 center1 = glm::vec4(offset.x,offset.y,offset.z,1);
    glm::vec4 center2 = glm::vec4(offset.x,offset.y+h,offset.z+shear,1);

    glm::vec4 positions[4];

    for(int i=0;i<360;i++)
    {
        double d1 = i*M_PI/180, d2;
        if(i >=180)
        	d2 = (i+60)*M_PI/180; 
        else
        	d2 = (i+1)*M_PI/180; 
        positions[0] = glm::vec4(a1*cos(d1),0,b1*sin(d1),1); colors1[0] = color1;
        positions[1] = glm::vec4(a2*cos(d1),h,b2*sin(d1)+shear,1); colors1[1] = color2;
        positions[2] = glm::vec4(a1*cos(d2),0,b1*sin(d2),1); colors1[2] = color1;
        positions[3] = glm::vec4(a2*cos(d2),h,b2*sin(d2)+shear,1); colors1[3] = color2;
        for(int j=0;j<4;j++)
        {
            positions[j].x = positions[j].x + offset.x;
            positions[j].y = positions[j].y + offset.y;
            positions[j].z = positions[j].z + offset.z;
        }
        v_positions[tri_idx] = center1; v_colors[tri_idx] = color1; tri_idx++;
        v_positions[tri_idx] = positions[0]; v_colors[tri_idx] = color1; tri_idx++;
        v_positions[tri_idx] = positions[2]; v_colors[tri_idx] = color1; tri_idx++;
        v_positions[tri_idx] = center2; v_colors[tri_idx] = color2; tri_idx++;
        v_positions[tri_idx] = positions[1]; v_colors[tri_idx] = color2; tri_idx++; 
        v_positions[tri_idx] = positions[3]; v_colors[tri_idx] = color2; tri_idx++;
        quad(v_positions,v_colors,positions,&tri_idx,0,1,3,2);

        if(i>=180)
        	i+=59;
    }

    csX75::HNode* node = new csX75::HNode(parent,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
    return node;
}

//! hexagonal lid for box
csX75::HNode* lid(float r0,float h0,glm::vec4 offset,csX75::HNode* parent,glm::vec4 color1,glm::vec4 color2)
{
    const int num_vertices = 48;
    glm::vec4 v_positions[num_vertices];
    glm::vec4 v_colors[num_vertices];
    glm::vec4 positions[8];
    int tri_idx = 0;
    float r = r0*size, h = h0*size;

    positions[0] = glm::vec4(-r,0,0,1.0);
    positions[1] = glm::vec4(-r/2,0,-sqrt(3)*r/2,1.0);
    positions[2] = glm::vec4(r/2,0,-sqrt(3)*r/2,1.0);
    positions[3] = glm::vec4(r,0,0,1.0);
    positions[4] = glm::vec4(r/2,0,sqrt(3)*r/2,1.0);
    positions[5] = glm::vec4(-r/2,0,sqrt(3)*r/2,1.0);

    for(int i=0;i<6;i++)
    {
        positions[i].x = positions[i].x + size*offset.x;
        positions[i].y = positions[i].y + size*offset.y;
        positions[i].z = positions[i].z + size*offset.z;
        colors1[i] = color1;
    }

    quad(v_positions,v_colors,positions,&tri_idx, 0,1,2,3);
    quad(v_positions,v_colors,positions,&tri_idx, 0,3,4,5);

    for(int i=0;i<6;i++)
    {    
        positions[6] = positions[i];
        positions[7] = positions[(i+1)%6];
        positions[6].y = positions[6].y + h;
        positions[7].y = positions[7].y + h;
        colors1[i] = color2;
        colors1[(i+1)%6] = color2;
        colors1[6] = color2;
        colors1[7] = color2;
        
        quad(v_positions,v_colors,positions,&tri_idx,i,(i+1)%6,7,6);
    }
    csX75::HNode* node = new csX75::HNode(parent,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
    return node;
}

//!  a hexagon to connect interior and exterior hexagonal lids
csX75::HNode* hexagon(float r10,float r20,glm::vec4 offset, csX75::HNode* parent,glm::vec4 color)
{
    const int num_vertices = 36;
    glm::vec4 v_positions[num_vertices];
    glm::vec4 v_colors[num_vertices];
    glm::vec4 positions[12];
    int tri_idx = 0;
    float r1 = r10*size, r2 = r20*size;
    
    positions[0] = glm::vec4(-r1,0,0,1.0);
    positions[1] = glm::vec4(-r1/2,0,-sqrt(3)*r1/2,1.0);
    positions[2] = glm::vec4(r1/2,0,-sqrt(3)*r1/2,1.0);
    positions[3] = glm::vec4(r1,0,0,1.0);
    positions[4] = glm::vec4(r1/2,0,sqrt(3)*r1/2,1.0);
    positions[5] = glm::vec4(-r1/2,0,sqrt(3)*r1/2,1.0);

    positions[6] = glm::vec4(-r2,0,0,1.0);
    positions[7] = glm::vec4(-r2/2,0,-sqrt(3)*r2/2,1.0);
    positions[8] = glm::vec4(r2/2,0,-sqrt(3)*r2/2,1.0);
    positions[9] = glm::vec4(r2,0,0,1.0);
    positions[10] = glm::vec4(r2/2,0,sqrt(3)*r2/2,1.0);
    positions[11] = glm::vec4(-r2/2,0,sqrt(3)*r2/2,1.0);

    for(int i=0;i<12;i++)
        colors1[i] = color;

    for(int i=0;i<6;i++)
    {
        quad(v_positions,v_colors,positions,&tri_idx, i,(i+1)%6,(i+1)%6+6,i+6);
    }

    csX75::HNode* node = new csX75::HNode(parent,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
    return node;
}

//! frustum of a cone
csX75::HNode* cylinder(float r10,float r20,float h0,glm::vec4 offset,csX75::HNode* parent,glm::vec4 color1,glm::vec4 color2)
{
    const int num_vertices = 12*360;
    glm::vec4 v_positions[num_vertices];
    glm::vec4 v_colors[num_vertices];
    int tri_idx = 0;
    float r1 = r10*size;
    float r2 = r20*size;
    float h = h0*size;

    offset.x *= size; offset.y *= size; offset.z *= size;
    glm::vec4 center1 = glm::vec4(offset.x,offset.y,offset.z,1);
    glm::vec4 center2 = glm::vec4(offset.x,offset.y+h,offset.z,1);

    glm::vec4 positions[4];

    for(int i=0;i<360;i++)
    {
        double d1 = i*M_PI/180, d2 = (i+1)*M_PI/180; 
        positions[0] = glm::vec4(r1*cos(d1),0,r1*sin(d1),1); colors1[0] = color1;
        positions[1] = glm::vec4(r2*cos(d1),h,r2*sin(d1),1); colors1[1] = color2;
        positions[2] = glm::vec4(r1*cos(d2),0,r1*sin(d2),1); colors1[2] = color1;
        positions[3] = glm::vec4(r2*cos(d2),h,r2*sin(d2),1); colors1[3] = color2;
        for(int j=0;j<4;j++)
        {
            positions[j].x = positions[j].x + offset.x;
            positions[j].y = positions[j].y + offset.y;
            positions[j].z = positions[j].z + offset.z;
        }
        v_positions[tri_idx] = center1; v_colors[tri_idx] = color1; tri_idx++;
        v_positions[tri_idx] = positions[0]; v_colors[tri_idx] = color1; tri_idx++;
        v_positions[tri_idx] = positions[2]; v_colors[tri_idx] = color1; tri_idx++;
        v_positions[tri_idx] = center2; v_colors[tri_idx] = color2; tri_idx++;
        v_positions[tri_idx] = positions[1]; v_colors[tri_idx] = color2; tri_idx++; 
        v_positions[tri_idx] = positions[3]; v_colors[tri_idx] = color2; tri_idx++;
        quad(v_positions,v_colors,positions,&tri_idx,0,1,3,2);
    }

    csX75::HNode* node = new csX75::HNode(parent,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
    return node;
}

//! frustum of a cone whose base is ellipse (not circle) with shear option on height direction
csX75::HNode* ellipsoid(float a10,float b10,float a20,float b20,float h0,glm::vec4 offset,float shear0,csX75::HNode* parent,glm::vec4 color1,glm::vec4 color2)
{
    const int num_vertices = 12*360;
    glm::vec4 v_positions[num_vertices];
    glm::vec4 v_colors[num_vertices];
    int tri_idx = 0;
    float a1 = a10*size, b1 = b10*size;
    float a2 = a20*size, b2 = b20*size;
    float h = h0*size;
    float shear = shear0*size;

    offset.x *= size; offset.y *= size; offset.z *= size;
    glm::vec4 center1 = glm::vec4(offset.x,offset.y,offset.z,1);
    glm::vec4 center2 = glm::vec4(offset.x,offset.y+h,offset.z+shear,1);

    glm::vec4 positions[4];

    for(int i=0;i<360;i++)
    {
        double d1 = i*M_PI/180, d2 = (i+1)*M_PI/180; 
        positions[0] = glm::vec4(a1*cos(d1),0,b1*sin(d1),1); colors1[0] = color1;
        positions[1] = glm::vec4(a2*cos(d1),h,b2*sin(d1)+shear,1); colors1[1] = color2;
        positions[2] = glm::vec4(a1*cos(d2),0,b1*sin(d2),1); colors1[2] = color1;
        positions[3] = glm::vec4(a2*cos(d2),h,b2*sin(d2)+shear,1); colors1[3] = color2;
        for(int j=0;j<4;j++)
        {
            positions[j].x = positions[j].x + offset.x;
            positions[j].y = positions[j].y + offset.y;
            positions[j].z = positions[j].z + offset.z;
        }
        v_positions[tri_idx] = center1; v_colors[tri_idx] = color1; tri_idx++;
        v_positions[tri_idx] = positions[0]; v_colors[tri_idx] = color1; tri_idx++;
        v_positions[tri_idx] = positions[2]; v_colors[tri_idx] = color1; tri_idx++;
        v_positions[tri_idx] = center2; v_colors[tri_idx] = color2; tri_idx++;
        v_positions[tri_idx] = positions[1]; v_colors[tri_idx] = color2; tri_idx++; 
        v_positions[tri_idx] = positions[3]; v_colors[tri_idx] = color2; tri_idx++;
        quad(v_positions,v_colors,positions,&tri_idx,0,1,3,2);
    }

    csX75::HNode* node = new csX75::HNode(parent,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
    return node;
}

float get_r(float a1,float a2,float h,float x)
{
    float r = 2.1*(a2+a1)/3;
    if(x < 2*h/3)
        return r - (r-a1)*(2*h/3-x)*(2*h/3-x)/((2*h/3)*(2*h/3)) ;
    else 
        return r - (r-a2)*(x-2*h/3)*(x-2*h/3)/((h/3)*(h/3)) ;
}

// rugby ball with both ends cut off (not used)
csX75::HNode* ellipsoid2(float a10,float b10,float a20,float b20,float h0,glm::vec4 offset,csX75::HNode* parent,glm::vec4 color1,glm::vec4 color2)
{
    const int num_vertices = 360*21*6;
    glm::vec4 v_positions[num_vertices];
    glm::vec4 v_colors[num_vertices];
    int tri_idx = 0;
    float a1 = a10*size, b1 = b10*size;
    float a2 = a20*size, b2 = b20*size;
    float h = h0*size;

    offset.x *= size; offset.y *= size; offset.z *= size;
    glm::vec4 center1 = glm::vec4(offset.x,offset.y,offset.z,1);
    glm::vec4 center2 = glm::vec4(offset.x,offset.y+h,offset.z,1);

    glm::vec4 positions[4];

    for(int k=0;k<20;k++)
    {
        float rx1 = get_r(a1,a2,h,(k)*h/20);
        float ry1 = get_r(b1,b2,h,(k)*h/20);
        float rx2 = get_r(a1,a2,h,(k+1)*h/20);
        float ry2 = get_r(b1,b2,h,(k+1)*h/20);
        for(int i=0;i<360;i++)
        {
            double d1 = i*M_PI/180, d2 = (i+1)*M_PI/180; 
            positions[0] = glm::vec4(rx1*cos(d1),(k)*h/20,ry1*sin(d1),1);
            positions[1] = glm::vec4(rx2*cos(d1),(k+1)*h/20,ry2*sin(d1),1);
            positions[2] = glm::vec4(rx1*cos(d2),(k)*h/20,ry1*sin(d2),1);
            positions[3] = glm::vec4(rx2*cos(d2),(k+1)*h/20,ry2*sin(d2),1);
            for(int j=0;j<4;j++)
            {
                positions[j].x = positions[j].x + offset.x;
                positions[j].y = positions[j].y + offset.y;
                positions[j].z = positions[j].z + offset.z;
            }

            if(k == 0)
            {
                v_positions[tri_idx] = center1; tri_idx++;
                v_positions[tri_idx] = positions[0]; tri_idx++;
                v_positions[tri_idx] = positions[2]; tri_idx++;
            }
            if(k == 19)
            {
                v_positions[tri_idx] = center2; tri_idx++;
                v_positions[tri_idx] = positions[1]; tri_idx++; 
                v_positions[tri_idx] = positions[3]; tri_idx++;
            }
            quad(v_positions,v_colors,positions,&tri_idx,0,1,3,2);
        }
    }
    for(int i=0;i<num_vertices;i++) v_colors[i] = skincolor1;

    csX75::HNode* node = new csX75::HNode(parent,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
    return node;
}

//! ellipical surface frustum for skirt of human
csX75::HNode* ellipse_surface(float a10,float b10,float a20,float b20,float h0,glm::vec4 offset,csX75::HNode* parent,glm::vec4 color1,glm::vec4 color2)
{
    const int num_vertices = 6*360;
    glm::vec4 v_positions[num_vertices];
    glm::vec4 v_colors[num_vertices];
    int tri_idx = 0;
    float a1 = a10*size, b1 = b10*size;
    float a2 = a20*size, b2 = b20*size;
    float h = h0*size;

    offset.x *= size; offset.y *= size; offset.z *= size;

    glm::vec4 positions[4];

    for(int i=0;i<360;i++)
    {
        double d1 = i*M_PI/180, d2 = (i+1)*M_PI/180; 
        positions[0] = glm::vec4(a1*cos(d1),0,b1*sin(d1),1); colors1[0] = color1;
        positions[1] = glm::vec4(a2*cos(d1),h,b2*sin(d1),1); colors1[1] = color2;
        positions[2] = glm::vec4(a1*cos(d2),0,b1*sin(d2),1); colors1[2] = color1;
        positions[3] = glm::vec4(a2*cos(d2),h,b2*sin(d2),1); colors1[3] = color2;
        for(int j=0;j<4;j++)
        {
            positions[j].x = positions[j].x + offset.x;
            positions[j].y = positions[j].y + offset.y;
            positions[j].z = positions[j].z + offset.z;
        }
        quad(v_positions,v_colors,positions,&tri_idx,0,1,3,2);
    }

    csX75::HNode* node = new csX75::HNode(parent,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
    return node;
}

//! sphere with option for different radii on different axes (ellipsoid)
csX75::HNode* sphere(float a0,float b0,float c0,glm::vec4 offset,csX75::HNode* parent,glm::vec4 color)
{
    const int num_vertices = 90*180*6;
    glm::vec4 v_positions[num_vertices];
    glm::vec4 v_colors[num_vertices];
    int tri_idx = 0;
    float a = a0*size, b = b0*size, c = c0*size;
    offset.x *= size; offset.y *= size; offset.z *= size;

    glm::vec4 positions[4];
    for(int i=0;i<90;i++)
    {
        for(int j=0;j<180;j++)
        {
            double i1 = 2*i*M_PI/180, i2 = 2*(i+1)*M_PI/180; 
            double j1 = 2*j*M_PI/180, j2 = 2*(j+1)*M_PI/180;
            positions[0] = glm::vec4(a*sin(i1)*cos(j1),b*cos(i1),c*sin(i1)*sin(j1),1);
            positions[1] = glm::vec4(a*sin(i1)*cos(j2),b*cos(i1),c*sin(i1)*sin(j2),1);
            positions[2] = glm::vec4(a*sin(i2)*cos(j2),b*cos(i2),c*sin(i2)*sin(j2),1);
            positions[3] = glm::vec4(a*sin(i2)*cos(j1),b*cos(i2),c*sin(i2)*sin(j1),1);
            for(int k=0;k<4;k++)
            {
                positions[k].x = positions[k].x + offset.x;
                positions[k].y = positions[k].y + offset.y;
                positions[k].z = positions[k].z + offset.z;
            }
            quad(v_positions,v_colors,positions,&tri_idx,0,1,2,3);
        }
    }

    for(int i=0;i<num_vertices;i++) 
        v_colors[i] = color;

    csX75::HNode* node = new csX75::HNode(parent,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
    return node;
}

//! triangular prism 
csX75::HNode* prism(float b0,float l0,float h0,glm::vec4 offset,csX75::HNode* parent,glm::vec4 color1,glm::vec4 color2)
{
    const int num_vertices = 12;
    glm::vec4 v_positions[num_vertices];
    glm::vec4 v_colors[num_vertices];
    int tri_idx = 0;
    float b = b0*size, l = l0*size, h = h0*size;
    offset.x *= size; offset.y *= size; offset.z *= size;

    glm::vec4 positions[4];
    positions[0] = glm::vec4(0,h,0,1);
    positions[1] = glm::vec4(0,0,b/2,1);
    positions[2] = glm::vec4(l/2,-h/3,-b/2,1);
    positions[3] = glm::vec4(-l/2,-h/3,-b/2,1);

    for(int k=0;k<4;k++){
        positions[k].x = positions[k].x + offset.x;
        positions[k].y = positions[k].y + offset.y;
        positions[k].z = positions[k].z + offset.z;
    }

    v_positions[tri_idx] = positions[0]; v_colors[tri_idx] = color1; tri_idx++;
    v_positions[tri_idx] = positions[1]; v_colors[tri_idx] = color2; tri_idx++;
    v_positions[tri_idx] = positions[2]; v_colors[tri_idx] = color1; tri_idx++;

    v_positions[tri_idx] = positions[0]; v_colors[tri_idx] = color1; tri_idx++;
    v_positions[tri_idx] = positions[1]; v_colors[tri_idx] = color2; tri_idx++;
    v_positions[tri_idx] = positions[3]; v_colors[tri_idx] = color1; tri_idx++;

    v_positions[tri_idx] = positions[0]; v_colors[tri_idx] = color1; tri_idx++;
    v_positions[tri_idx] = positions[2]; v_colors[tri_idx] = color1; tri_idx++;
    v_positions[tri_idx] = positions[3]; v_colors[tri_idx] = color1; tri_idx++;

    v_positions[tri_idx] = positions[1]; v_colors[tri_idx] = color2; tri_idx++;
    v_positions[tri_idx] = positions[2]; v_colors[tri_idx] = color1; tri_idx++;
    v_positions[tri_idx] = positions[3]; v_colors[tri_idx] = color1; tri_idx++;

    csX75::HNode* node = new csX75::HNode(parent,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
    return node;
}

//! equations for upper and lower surfaces of fox tail
float eqn1(float x, float h, float l,float ang)
{
    return l*(cos(M_PI*x/h - M_PI*ang/180)-cos(M_PI*ang/180))/cos(M_PI*ang/180);
}

float eqn2(float x, float h, float l, float ang)
{
    return l*(cos(M_PI*x/h + M_PI*ang/180)-cos(M_PI*ang/180))/cos(M_PI*ang/180);
}

//! tail of fox
csX75::HNode* tail(float h0,float l0,float ang,float b0,csX75::HNode* parent,glm::vec4 color1, glm::vec4 color2)
{
    const int num_vertices = 360*6*50;
    glm::vec4 v_positions[num_vertices];
    glm::vec4 v_colors[num_vertices];
    glm::vec4 positions[4];
    int tri_idx = 0;
    float h = h0*size, l = l0*size, b = b0*size;

    
    for(int k=0;k<50;k++){
        float x1 = k*h/50, x2 = (k+1)*h/50;
        float y1 = ( eqn1(x1,h,l,ang)+eqn2(x1,h,l,ang) )/2;
        float y2 = ( eqn1(x2,h,l,ang)+eqn2(x2,h,l,ang) )/2;
        float r1 = ( eqn1(x1,h,l,ang)-eqn2(x1,h,l,ang) )/2;
        float r2 = ( eqn1(x2,h,l,ang)-eqn2(x2,h,l,ang) )/2;
        float b1 = sqrt(b*b - b*b*(x1-h/2)*(x1-h/2)/(h*h/4))/2;
        float b2 = sqrt(b*b - b*b*(x2-h/2)*(x2-h/2)/(h*h/4))/2;

        for(int i=0;i<360;i++){
            double d1 = i*M_PI/180, d2 = (i+1)*M_PI/180; 
            positions[0] = glm::vec4(x1,y1+r1*cos(d1),b1*sin(d1),1); 
            positions[1] = glm::vec4(x1,y1+r1*cos(d2),b1*sin(d2),1); 
            positions[2] = glm::vec4(x2,r2*cos(d1)+y1,b2*sin(d1),1); 
            positions[3] = glm::vec4(x2,r2*cos(d2)+y2,b2*sin(d2),1); 
            
            for(int j=0;j<4;j++){
                colors1[j].x = (color1.x*k+(50-k)*color2.x)/50;
                colors1[j].y = (color1.y*k+(50-k)*color2.y)/50;
                colors1[j].z = (color1.z*k+(50-k)*color2.z)/50;
                colors1[j].w = (color1.w*k+(50-k)*color2.w)/50;
            }
           
            quad(v_positions,v_colors,positions,&tri_idx,0,1,3,2);
        }
    }

    csX75::HNode* node = new csX75::HNode(parent,num_vertices,v_positions,v_colors,sizeof(v_positions),sizeof(v_colors));
    return node;
}
