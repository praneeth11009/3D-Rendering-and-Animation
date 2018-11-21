#include "human.hpp"

csX75::HNode* get_human(float humansize,glm::vec4 offset)
{
    /* First character */

    //lower torso (root of human) 
    torso2 = sphere(0.45,0.3,0.3,glm::vec4(0,0,0,1),NULL,bluecolor);
    torso2->change_parameters(offset.x,offset.y,offset.z,0.0,0.0,0.0,humansize);
    torso2->set_constraints(1,0,1,0,1,0);
    
    //upper torso (abdomen)
    torso3 = ellipsoid(0.45,0.3,0.45+0.35*1.2/1.5,0.3+0.3*1.2/1.5,1.2,glm::vec4(0,0,0,1),0,torso2,bluecolor,lightbluecolor);
    csX75::HNode* torso = ellipsoid(0.45+0.35*1.2/1.5,0.3+0.3*1.2/1.5,0.8,0.4,0.3,glm::vec4(0,0,0,1),0,torso3,skincolor,skincolor);
    torso->set_constraints(0,0,0,0,0,0);
    torso->change_parameters(0.0,1.2,0.0,0.0,0.0,0.0,humansize); 
    torso3->set_constraints(-30,90,-80,80,-15,15);
    torso3->change_parameters(0.0,0,0.0,0.0,0.0,0.0,humansize); 

    //connection between neck and upper torso
    torso1 = ellipsoid(0.8,0.4,0.25,0.2,0.25,glm::vec4(0,0,0,1),0,torso3,skincolor,darkskincolor);
    torso1->set_constraints(1,0,1,0,1,0);
    torso1->change_parameters(0,1.5,0,0,0,0,humansize);

    //skirt of human
    skirt = ellipse_surface(2.5,2.5,0.45,0.3,1.3,glm::vec4(0,0,0,1),torso2,lightbluecolor,bluecolor);
    skirt->set_constraints(1,0,1,0,1,0);
    skirt->change_parameters(0,-1.3,0,0,0,0,humansize);

    //belt / ribbon for skirt
    csX75::HNode* ribbon1 = ellipsoid(0.475,0.325,0.475,0.325,0.15,glm::vec4(0,0,0,1),0,torso3,redcolor,redcolor);
    ribbon1->set_constraints(0,0,0,0,0,0);
    ribbon1->change_parameters(0,0,0,0,0,0,humansize);
        
    //neck
    neck = ellipsoid(0.25,0.2,0.25,0.2,0.3,glm::vec4(0,0,0,1),0,torso1,darkskincolor,skincolor);
    neck->set_constraints(-20,20,-20,20,-20,20);
    neck->change_parameters(0.0,0.25,0.0,0.0,0.0,0.0,humansize); 

    //neck joint
    csX75::HNode* neck_joint = sphere(0.25,0.2,0.2,glm::vec4(0,0,0,1),torso1,darkskincolor);
    neck_joint->set_constraints(0,0,0,0,0,0);
    neck_joint->change_parameters(0,0.25,0,0,0,0,humansize);
    
    //head
    head = sphere(0.4,0.45,0.35,glm::vec4(0,0,0,1),neck,skincolor);
    head->set_constraints(-30,60,-80,80,-30,30);
    head->change_parameters(0.0,0.55,0.07,0.0,0.0,0.0,humansize); 

    //nose
    csX75::HNode* nose = prism(0.15,0.15,0.2,glm::vec4(0,0,0,1),head,skincolor,darkskincolor);
    nose->set_constraints(0,0,0,0,0,0);    
    nose->change_parameters(0,-0.1,0.35,0,0,0,humansize);

    //hair near face
    csX75::HNode* hair = sphere(0.45,0.45,0.42,glm::vec4(0,0,0,1),head,browncolor1);
    //longer part of hair which is tied as bun
    csX75::HNode* hair2 = sphere(0.3,0.3,0.3,glm::vec4(0,0,0,1),hair,browncolor2);
    hair2->set_constraints(0,0,0,0,0,0);
    hair2->change_parameters(0,0.6,0,0,0,0,humansize); 
    hair->set_constraints(0,0,0,0,0,0);
    hair->change_parameters(0,0.15,-0.15,-55,0,0,humansize);

    //left upper leg
    left_ul = cylinder(0.2,0.35,1.9,glm::vec4(0,-1.9,0,1),torso2,darkwhitecolor,darkerwhitecolor);
    //left ankle joint
    csX75::HNode* left_ankle = sphere(0.2,0.2,0.2,glm::vec4(0,0,0,1),left_ul,darkwhitecolor);
    left_ankle->set_constraints(0,0,0,0,0,0);
    left_ankle->change_parameters(0,-1.9,0,0,0,0,humansize);
    left_ul->set_constraints(-60,60,-90,45,-45,0);
    left_ul->change_parameters(-0.3,-0.3,0.0,0.0,0.0,0.0,humansize);
    
    //right upper leg
    right_ul = cylinder(0.2,0.35,1.9,glm::vec4(0,-1.9,0,1),torso2,darkwhitecolor,darkerwhitecolor);
    //right ankle joint
    csX75::HNode* right_ankle = sphere(0.2,0.2,0.2,glm::vec4(0,0,0,1),right_ul,darkwhitecolor);
    right_ankle->set_constraints(0,0,0,0,0,0);
    right_ankle->change_parameters(0,-1.9,0,0,0,0,humansize);
    right_ul->set_constraints(-60,60,-45,90,0,45);
    right_ul->change_parameters(0.3,-0.3,0.0,0.0,0.0,0.0,humansize);
    
    //left knee
    left_ll = sphere(0.21,0.5,0.21,glm::vec4(0,-0.3,0,1),left_ul,darkwhitecolor);
    left_ll->set_constraints(0,90,0,0,0,0);
    left_ll->change_parameters(0.0,-1.9,0,0.0,0.0,0.0,humansize); 

    //left lower leg
    csX75::HNode* left_leg1 = ellipsoid(0.12,0.12,0.18,0.18,1.6,glm::vec4(0,-1.6,0,1),0,left_ll,darkwhitecolor,darkwhitecolor);
    left_leg1->set_constraints(0,0,0,0,0,0);
    left_leg1->change_parameters(0,-0.35,0,0,0,0,humansize);
 
    //right knee
    right_ll = sphere(0.21,0.5,0.21,glm::vec4(0,-0.3,0,1),right_ul,darkwhitecolor);
    right_ll->set_constraints(0,90,0,0,0,0);
    right_ll->change_parameters(0.0,-1.9,0,0.0,0.0,0.0,humansize);

    //right lower leg
    csX75::HNode* right_leg1 = ellipsoid(0.12,0.12,0.18,0.18,1.6,glm::vec4(0,-1.6,0,1),0,right_ll,darkwhitecolor,darkwhitecolor);
    right_leg1->set_constraints(0,0,0,0,0,0);
    right_leg1->change_parameters(0,-0.35,0,0,0,0,humansize);

    //left feet
    left_ft = sphere(0.13,0.12,0.13,glm::vec4(0,-0.12,0,1),left_ll,redcolor);
    left_ft->set_constraints(-10,10,0,0,0,0);
    left_ft->change_parameters(0.0,-1.8,0,0.0,0.0,0.0,humansize);

    //left shoe
    csX75::HNode* left_shoe = ellipsoid(0.12,0.1,0.08,0.03,0.35,glm::vec4(0,0,0,1),0,left_ft,redcolor,redcolor);
    left_shoe->set_constraints(0,0,0,0,0,0);
    left_shoe->change_parameters(0,-0.2,0,180,0,0,humansize);
    
    //right feet
    right_ft = sphere(0.13,0.12,0.13,glm::vec4(0,-0.12,0,1),right_ll,redcolor);
    right_ft->set_constraints(-10,10,0,0,0,0);
    right_ft->change_parameters(0.0,-1.8,0,0.0,0.0,0.0,humansize);

    //right shoe
    csX75::HNode* right_shoe = ellipsoid(0.12,0.1,0.08,0.03,0.35,glm::vec4(0,0,0,1),0,right_ft,redcolor,redcolor);
    right_shoe->set_constraints(0,0,0,0,0,0);
    right_shoe->change_parameters(0,-0.2,0,180,0,0,humansize);
 
    //left shoulder
    left_sh = sphere(0.19,0.19,0.19,glm::vec4(0,0,0,1),torso1,skincolor);
    //left ball and socket joint
    csX75::HNode* temp = cylinder(0.15,0.15,0.3,glm::vec4(0,0,0,1),left_sh,skincolor,skincolor);
    temp->change_parameters(0,0,0,0,0,-90,humansize);
    left_sh->set_constraints(0,0,0,0,0,0);
    left_sh->change_parameters(-0.7,-0.17,0.0,0.0,0.0,0.0,humansize);
    
    //right shoulder
    right_sh = sphere(0.19,0.19,0.19,glm::vec4(0,0,0,1),torso1,skincolor);
    //right ball and socket joint
    csX75::HNode* temp2 = cylinder(0.15,0.15,0.3,glm::vec4(0,0,0,1),right_sh,skincolor,skincolor);
    temp2->change_parameters(0,0,0,0,0,90,humansize);
    right_sh->set_constraints(0.2,0,0,0,0,0);
    right_sh->change_parameters(0.7,-0.17,0.0,0.0,0.0,0.0,humansize);

    //left upper arm
    left_ua = ellipsoid(0.16,0.16,0.16,0.16,1.2,glm::vec4(0,-1.1,0,1),0,left_sh,darkskincolor,skincolor);
    //left elbow joint
    csX75::HNode* left_elbow = sphere(0.16,0.16,0.16,glm::vec4(0,0,0,1),left_ua,darkskincolor);
    left_elbow->set_constraints(0,0,0,0,0,0);
    left_elbow->change_parameters(0,-1,0,0,0,0,humansize);
    left_ua->set_constraints(-90,90,-45,45,-150,-30);
    left_ua->change_parameters(-0.01,-0.01,0.0,0.0,0.0,-90.0,humansize);
    
    //right upper arm
    right_ua = ellipsoid(0.16,0.16,0.16,0.16,1.2,glm::vec4(0,-1.1,0,1),0,right_sh,darkskincolor,skincolor);
    //right elbow joint
    csX75::HNode* right_elbow = sphere(0.16,0.16,0.16,glm::vec4(0,0,0,1),right_ua,darkskincolor);
    right_elbow->set_constraints(0,0,0,0,0,0);
    right_elbow->change_parameters(0,-1,0,0,0,0,humansize);
    right_ua->set_constraints(-90,90,-45,45,30,150);
    right_ua->change_parameters(0.01,-0.01,0.0,0.0,0.0,90.0,humansize);
    
    //left lower arm
    left_la = ellipsoid(0.1,0.06,0.16,0.16,1,glm::vec4(0,-1,0,1),0,left_ua,darkwhitecolor,darkwhitecolor);
    left_la->set_constraints(-150,0,0,0,0,0);
    left_la->change_parameters(0.0,-1,0.0,0.0,0.0,0.0,humansize);
    
    //right lower arm
    right_la = ellipsoid(0.1,0.06,0.16,0.16,1,glm::vec4(0,-1,0,1),0,right_ua,darkwhitecolor,darkwhitecolor);
    right_la->set_constraints(-150,0,0,0,0,0);
    right_la->change_parameters(0.0,-1,0.0,0.0,0.0,0.0,humansize);

    //left palm
    left_wr = ellipsoid(0.14,0.06,0.1,0.06,0.2,glm::vec4(0,-0.2,0,1),0,left_la,darkwhitecolor,darkwhitecolor);
    left_wr->set_constraints(-90,30,-180,0,0,0);
    left_wr->change_parameters(0.0,-1,0.02,0.0,0.0,0.0,humansize);

    //left lower palm (i.e., fingers part)
    csX75:: HNode* left_wr2 = ellipsoid(0.06,0.04,0.14,0.06,0.3,glm::vec4(0,-0.3,0,1),0,left_wr,darkwhitecolor,darkwhitecolor);
    left_wr2->set_constraints(0,0,0,0,0,0);
    left_wr2->change_parameters(0,-0.2,0,0,0,0,humansize);
    
    //right palm
    right_wr = ellipsoid(0.14,0.06,0.1,0.06,0.2,glm::vec4(0,-0.2,0,1),0,right_la,darkwhitecolor,darkwhitecolor);
    right_wr->set_constraints(-90,30,0,180,0,0);
    right_wr->change_parameters(0.0,-1,0.02,0.0,0.0,0.0,humansize);

    //right lower palm (i.e., fingers part)
    csX75:: HNode* right_wr2 = ellipsoid(0.06,0.04,0.14,0.06,0.3,glm::vec4(0,-0.3,0,1),0,right_wr,darkwhitecolor,darkwhitecolor);
    right_wr2->set_constraints(0,0,0,0,0,0);
    right_wr2->change_parameters(0,-0.2,0,0,0,0,humansize);

    return torso2;
}