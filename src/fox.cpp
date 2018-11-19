#include "fox.hpp"

csX75::HNode* get_fox(float foxsize,glm::vec4 offset)
{

  /*Second Character*/

  //front abdominal body (root of fox)
  an_torso1 = ellipsoid(0.6,0.8,0.6,0.6,2,glm::vec4(0,0,0,1),0,NULL,browncolor2,browncolor2);
  an_torso1->change_parameters(offset.x,offset.y,offset.z,-90,0,90,foxsize);
  an_torso1->set_constraints(1,0,1,0,1,0);

  //back abdomen
  csX75::HNode* an_torso2 = ellipsoid(0.6,0.6,0.6,0.6,0.75,glm::vec4(0,0,0,1),0,an_torso1,browncolor2,browncolor1);
  an_torso2->change_parameters(0,2,0,0,0,0,foxsize);
  an_torso2->set_constraints(0,0,0,0,0,0);

  //a connecting sphere so that rotation of neck doesn't make it as a cut at the neck
  csX75::HNode* t1_neck_sphere = sphere(0.6,0.6,0.6,glm::vec4(0,0,0,1),an_torso1,browncolor2);
  t1_neck_sphere->change_parameters(0,0,0.15,0,0,0,foxsize);
  t1_neck_sphere->set_constraints(0,0,0,0,0,0);

  //back part of body
  csX75::HNode* t1_tail_sphere = sphere(0.6,0.5,0.6,glm::vec4(0,0,0,1),an_torso2,browncolor1);
  t1_tail_sphere->change_parameters(0,0.8,0,0,0,0,foxsize);
  t1_tail_sphere->set_constraints(0,0,0,0,0,0);

  //neck
  an_neck = ellipsoid(0.6,0.8,0.5,0.5,1.2,glm::vec4(0,0,0,1),-0.7,an_torso1,browncolor2,browncolor1);
  an_neck->change_parameters(0,0,0,180,0,0,foxsize);
  an_neck->set_constraints(180,215,0,0,0,0);

  //brain part of head
  an_head0 = cuboid2(0.5,0.55,0.4,0.4,0.6,glm::vec4(0,0,0,1),0.025,an_neck,browncolor1,browncolor1);
  an_head0->change_parameters(0,1.2,-0.75,0,0,0,foxsize);
  an_head0->set_constraints(0,0,-10,10,0,0);

  //middle part of head
  csX75::HNode* an_head1 = cuboid2(0.4,0.4,0.25,0.21,0.3,glm::vec4(0,0,0,1),0.07,an_head0,browncolor1,browncolor1);
  an_head1->change_parameters(0,0.6,0.025,0,0,0,foxsize);
  an_head1->set_constraints(0,0,0,0,0,0);

  //front part, i.e., mouth, etc...
  csX75::HNode* an_head2 = cuboid2(0.25,0.21,0.08,0.05,0.45,glm::vec4(0,0,0,1),-0.015,an_head1,browncolor1,browncolor2);
  an_head2->change_parameters(0,0.3,0.07,0,0,0,foxsize);
  an_head2->set_constraints(0,0,0,0,0,0);  

  //left ear
  csX75::HNode* ear_lu = cuboid(0.7,0.4,0.05,0,0,glm::vec4(0,0,0,1),0,an_head0,browncolor1,browncolor1);
  ear_lu->change_parameters(-0.3,0,-0.65,-100,-10,110,foxsize);
  ear_lu->set_constraints(0,0,0,0,0,0);

  //right ear
  csX75::HNode* ear_ru = cuboid(0.7,0.4,0.05,0,0,glm::vec4(0,0,0,1),0,an_head0,browncolor1,browncolor1);
  ear_ru->change_parameters(0.3,0,-0.65,-100,-10,70,foxsize);
  ear_ru->set_constraints(0,0,0,0,0,0);

  //left upper fore leg
  an_left_fla = ellipsoid(0.2,0.25,0.4,0.45,1.5,glm::vec4(0,-1.5,0,1),0.2,an_torso1,browncolor1,browncolor2);
  an_left_fla->change_parameters(-0.4,0.33,0,90,0,0,foxsize);
  an_left_fla->set_constraints(60,110,0,0,0,0);

  //left frontal ball and socket joint
  csX75::HNode* an_left_up_sphere = sphere(0.4,0.45,0.45,glm::vec4(0,0,0,1),an_left_fla,browncolor2);
  an_left_up_sphere->change_parameters(0,0,0.2,0,0,0,foxsize);
  an_left_up_sphere->set_constraints(0,0,0,0,0,0);

  //left lower fore leg
  an_left_fll = ellipsoid(0.15,0.17,0.2,0.25,1,glm::vec4(0,-1,0,1),0,an_left_fla,darkerwhitecolor,browncolor1);
  an_left_fll->change_parameters(0,-1.5,0,0,0,0,foxsize);
  an_left_fll->set_constraints(0,0,0,0,0,0);  

  //right upper fore leg
  an_right_fla = ellipsoid(0.2,0.25,0.4,0.45,1.5,glm::vec4(0,-1.5,0,1),0.2,an_torso1,browncolor1,browncolor2);
  an_right_fla->change_parameters(0.4,0.33,0,90,0,0,foxsize);
  an_right_fla->set_constraints(60,110,0,0,0,0);

  //right frontal ball and socket joint
  csX75::HNode* an_right_up_sphere = sphere(0.4,0.45,0.45,glm::vec4(0,0,0,1),an_right_fla,browncolor2);
  an_right_up_sphere->change_parameters(0,0,0.2,0,0,0,foxsize);
  an_right_up_sphere->set_constraints(0,0,0,0,0,0);

  //right lower fore leg
  an_right_fll = ellipsoid(0.15,0.17,0.2,0.25,1,glm::vec4(0,-1,0,1),0,an_right_fla,darkerwhitecolor,browncolor1);
  an_right_fll->change_parameters(0,-1.5,0,0,0,0,foxsize);
  an_right_fll->set_constraints(0,0,0,0,0,0); 

  //left front foot
  csX75::HNode* left_fft = ellipsoid(0.15,0.35,0.15,0.17,0.2,glm::vec4(0,0,0,1),-0.08,an_left_fll,browncolor2,browncolor2);
  left_fft->change_parameters(0,-1.2,0.09,0,0,0,foxsize);
  left_fft->set_constraints(0,0,0,0,0,0); 

  //right front foot
  csX75::HNode* right_fft = ellipsoid(0.15,0.35,0.15,0.17,0.2,glm::vec4(0,0,0,1),-0.08,an_right_fll,browncolor2,browncolor2);
  right_fft->change_parameters(0,-1.2,0.09,0,0,0,foxsize);
  right_fft->set_constraints(0,0,0,0,0,0); 

  //left upper hind leg
  an_left_hla = ellipsoid(0.2,0.25,0.4,0.75,1.6,glm::vec4(0,-1.6,0,1),0.5,an_torso2,browncolor2,browncolor1);
  an_left_hla->change_parameters(-0.4,1,0,90,0,0,foxsize);
  an_left_hla->set_constraints(70,110,0,0,0,0);

  //left back ball and socket joint
  csX75::HNode* an_left_up_sphere_bk = sphere(0.4,0.45,0.75,glm::vec4(0,0,0,1),an_left_hla,browncolor1);
  an_left_up_sphere_bk->change_parameters(0,0,0.5,0,0,0,foxsize);
  an_left_up_sphere_bk->set_constraints(0,0,0,0,0,0);

  ////left back hinge joint
  csX75::HNode* an_left_down_sphere_bk = sphere(0.2,0.25,0.25,glm::vec4(0,0,0,1),an_left_hla,browncolor1);
  an_left_down_sphere_bk->change_parameters(0,-1.6,0,0,0,0,foxsize);
  an_left_down_sphere_bk->set_constraints(0,0,0,0,0,0);

  //left lower hind leg
  an_left_hll = ellipsoid(0.15,0.17,0.2,0.25,0.9,glm::vec4(0,-0.9,0,1),0,an_left_hla,darkerwhitecolor,browncolor1);
  an_left_hll->change_parameters(0,-1.6,0,-20,0,0,foxsize);
  an_left_hll->set_constraints(0,0,0,0,0,0);

  //right upper hind leg
  an_right_hla = ellipsoid(0.2,0.25,0.4,0.75,1.6,glm::vec4(0,-1.6,0,1),0.5,an_torso2,browncolor2,browncolor1);
  an_right_hla->change_parameters(0.4,1,0,90,0,0,foxsize);
  an_right_hla->set_constraints(70,110,0,0,0,0);

  //right back ball and socket joint
  csX75::HNode* an_right_up_sphere_bk = sphere(0.4,0.45,0.75,glm::vec4(0,0,0,1),an_right_hla,browncolor1);
  an_right_up_sphere_bk->change_parameters(0,0,0.5,0,0,0,foxsize);
  an_right_up_sphere_bk->set_constraints(0,0,0,0,0,0);

  //right back hinge joint
  csX75::HNode* an_right_down_sphere_bk = sphere(0.2,0.25,0.25,glm::vec4(0,0,0,1),an_right_hla,browncolor1);
  an_right_down_sphere_bk->change_parameters(0,-1.6,0,0,0,0,foxsize);
  an_right_down_sphere_bk->set_constraints(0,0,0,0,0,0);

  //right lower hind leg
  an_right_hll = ellipsoid(0.15,0.17,0.2,0.25,0.9,glm::vec4(0,-0.9,0,1),0,an_right_hla,darkerwhitecolor,browncolor1);
  an_right_hll->change_parameters(0,-1.6,0,-20,0,0,foxsize);
  an_right_hll->set_constraints(0,0,0,0,0,0);

  //left ankle joint
  csX75::HNode* left_bft_sphere = sphere(0.15,0.12,0.17,glm::vec4(0,0,0,1),an_left_hll,browncolor2);
  left_bft_sphere->change_parameters(0,-0.9,0,20,0,0,foxsize);
  left_bft_sphere->set_constraints(0,0,0,0,0,0); 

  //left back foot
  csX75::HNode* left_bft = ellipsoid(0.15,0.35,0.15,0.17,0.2,glm::vec4(0,0,0,1),-0.05,an_left_hll,browncolor2,browncolor2);
  left_bft->change_parameters(0,-1.16,0.0,20,0,0,foxsize);
  left_bft->set_constraints(0,0,0,0,0,0);

  //right ankle joint
  csX75::HNode* right_bft_sphere = sphere(0.15,0.12,0.17,glm::vec4(0,0,0,1),an_right_hll,browncolor2);
  right_bft_sphere->change_parameters(0,-0.9,0,20,0,0,foxsize);
  right_bft_sphere->set_constraints(0,0,0,0,0,0); 

  //right back foot
  csX75::HNode* right_bft = ellipsoid(0.15,0.35,0.15,0.17,0.2,glm::vec4(0,0,0,1),-0.05,an_right_hll,browncolor2,browncolor2);
  right_bft->change_parameters(0,-1.16,0.0,20,0,0,foxsize);
  right_bft->set_constraints(0,0,0,0,0,0);

  //tail
  an_tail = tail(3,0.8,30,0.4,t1_tail_sphere,darkwhitecolor,browncolor1);
  an_tail->change_parameters(0,0,0.6,90,90,0,foxsize);
  an_tail->set_constraints(70,100,80,100,0,0);

  return an_torso1;
}