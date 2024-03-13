// This file was generated by SquareLine Studio
// SquareLine Studio version: SquareLine Studio 1.4.0
// LVGL version: 8.3.6
// Project name: test_LCD

#include "../ui.h"

void ui_Screen5_screen_init(void)
{
    ui_Screen5 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen5, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_Screen5, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_Screen5, 255, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_TabView1 = lv_tabview_create(ui_Screen5, LV_DIR_TOP, 50);
    lv_obj_set_width(ui_TabView1, 400);
    lv_obj_set_height(ui_TabView1, 700);
    lv_obj_set_align(ui_TabView1, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_TabView1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_radius(ui_TabView1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_color(ui_TabView1, lv_color_hex(0x000000), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_TabView1, 255, LV_PART_MAIN | LV_STATE_DEFAULT);


    ui_TabPage1 = lv_tabview_add_tab(ui_TabView1, "Title 1");

    ui_Colorwheel2 = lv_colorwheel_create(ui_TabPage1, true);
    lv_obj_set_width(ui_Colorwheel2, 150);
    lv_obj_set_height(ui_Colorwheel2, 150);
    lv_obj_set_align(ui_Colorwheel2, LV_ALIGN_CENTER);

    ui_TabPage2 = lv_tabview_add_tab(ui_TabView1, "Title 2");

    ui_Image13 = lv_img_create(ui_TabPage2);
    lv_img_set_src(ui_Image13, &ui_img_fire_urn_png);
    lv_obj_set_width(ui_Image13, LV_SIZE_CONTENT);   /// 400
    lv_obj_set_height(ui_Image13, LV_SIZE_CONTENT);    /// 960
    lv_obj_set_align(ui_Image13, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_Image13, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_Image13, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_TabPage3 = lv_tabview_add_tab(ui_TabView1, "Title 3");

    lv_obj_add_event_cb(ui_Screen5, ui_event_Screen5, LV_EVENT_ALL, NULL);

}
