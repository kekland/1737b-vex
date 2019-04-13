#include "main.h"
#include "pros/apix.h"

void screenInit()
{
  static lv_style_t primary_label;                 /*Styles can't be local variables*/
  lv_style_copy(&primary_label, &lv_style_pretty); /*Copy a built-in style as a starting point*/
  primary_label.text.color = LV_COLOR_WHITE;
  primary_label.text.font = &lv_font_dejavu_20;

  static lv_style_t secondary_label;               /*Styles can't be local variables*/
  lv_style_copy(&secondary_label, &primary_label); /*Copy a built-in style as a starting point*/
  secondary_label.text.color = LV_COLOR_GRAY;

  static lv_style_t background_style;
  lv_style_copy(&background_style, &lv_style_plain_color);
  background_style.body.radius = 8;
  background_style.body.main_color = LV_COLOR_WHITE;
  background_style.body.grad_color = LV_COLOR_WHITE;

  lv_obj_t *teamLabel = lv_label_create(lv_scr_act(), NULL);
  lv_obj_t *descriptionLabel = lv_label_create(lv_scr_act(), NULL);

  lv_label_set_text(teamLabel, "1737B");
  lv_label_set_style(teamLabel, &primary_label);

  lv_label_set_text(descriptionLabel, "Siranov sasatt");
  lv_label_set_style(descriptionLabel, &secondary_label);

  lv_obj_align(teamLabel, NULL, LV_ALIGN_CENTER, -130.0, -8.0);
  lv_obj_align(descriptionLabel, NULL, LV_ALIGN_CENTER, -130.0, 8.0);

  lv_obj_t *background = lv_obj_create(lv_scr_act(), NULL);
  lv_obj_set_style(background, &background_style);
  lv_obj_set_width(background, 220);
  lv_obj_set_height(background, 190);
  lv_obj_align(background, NULL, LV_ALIGN_CENTER, 110.0, 0.0);

  lv_obj_t *auton_label = lv_label_create(lv_scr_act(), NULL);

  lv_label_set_text(auton_label, "Select autonomous");
  lv_label_set_style(auton_label, &lv_style_pretty);
  lv_obj_align(auton_label, NULL, LV_ALIGN_CENTER, 110.0, -80.0);

  lv_obj_t *btn1 = lv_btn_create(lv_scr_act(), NULL); 
  lv_btn_set_action(btn1, LV_BTN_ACTION_CLICK, NULL);
  lv_obj_align(btn1, NULL, LV_ALIGN_CENTER, 110.0, -50.0);
}
