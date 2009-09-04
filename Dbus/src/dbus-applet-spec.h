/* Generated by dbus-binding-tool; do not edit! */


#ifndef __dbus_glib_marshal_cd_dbus_applet_MARSHAL_H__
#define __dbus_glib_marshal_cd_dbus_applet_MARSHAL_H__

#include	<glib-object.h>

G_BEGIN_DECLS

#ifdef G_ENABLE_DEBUG
#define g_marshal_value_peek_boolean(v)  g_value_get_boolean (v)
#define g_marshal_value_peek_char(v)     g_value_get_char (v)
#define g_marshal_value_peek_uchar(v)    g_value_get_uchar (v)
#define g_marshal_value_peek_int(v)      g_value_get_int (v)
#define g_marshal_value_peek_uint(v)     g_value_get_uint (v)
#define g_marshal_value_peek_long(v)     g_value_get_long (v)
#define g_marshal_value_peek_ulong(v)    g_value_get_ulong (v)
#define g_marshal_value_peek_int64(v)    g_value_get_int64 (v)
#define g_marshal_value_peek_uint64(v)   g_value_get_uint64 (v)
#define g_marshal_value_peek_enum(v)     g_value_get_enum (v)
#define g_marshal_value_peek_flags(v)    g_value_get_flags (v)
#define g_marshal_value_peek_float(v)    g_value_get_float (v)
#define g_marshal_value_peek_double(v)   g_value_get_double (v)
#define g_marshal_value_peek_string(v)   (char*) g_value_get_string (v)
#define g_marshal_value_peek_param(v)    g_value_get_param (v)
#define g_marshal_value_peek_boxed(v)    g_value_get_boxed (v)
#define g_marshal_value_peek_pointer(v)  g_value_get_pointer (v)
#define g_marshal_value_peek_object(v)   g_value_get_object (v)
#else /* !G_ENABLE_DEBUG */
/* WARNING: This code accesses GValues directly, which is UNSUPPORTED API.
 *          Do not access GValues directly in your code. Instead, use the
 *          g_value_get_*() functions
 */
#define g_marshal_value_peek_boolean(v)  (v)->data[0].v_int
#define g_marshal_value_peek_char(v)     (v)->data[0].v_int
#define g_marshal_value_peek_uchar(v)    (v)->data[0].v_uint
#define g_marshal_value_peek_int(v)      (v)->data[0].v_int
#define g_marshal_value_peek_uint(v)     (v)->data[0].v_uint
#define g_marshal_value_peek_long(v)     (v)->data[0].v_long
#define g_marshal_value_peek_ulong(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_int64(v)    (v)->data[0].v_int64
#define g_marshal_value_peek_uint64(v)   (v)->data[0].v_uint64
#define g_marshal_value_peek_enum(v)     (v)->data[0].v_long
#define g_marshal_value_peek_flags(v)    (v)->data[0].v_ulong
#define g_marshal_value_peek_float(v)    (v)->data[0].v_float
#define g_marshal_value_peek_double(v)   (v)->data[0].v_double
#define g_marshal_value_peek_string(v)   (v)->data[0].v_pointer
#define g_marshal_value_peek_param(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_boxed(v)    (v)->data[0].v_pointer
#define g_marshal_value_peek_pointer(v)  (v)->data[0].v_pointer
#define g_marshal_value_peek_object(v)   (v)->data[0].v_pointer
#endif /* !G_ENABLE_DEBUG */


/* BOOLEAN:BOXED,POINTER (/tmp/dbus-binding-tool-c-marshallers.IISSZU:1) */
extern void dbus_glib_marshal_cd_dbus_applet_BOOLEAN__BOXED_POINTER (GClosure     *closure,
                                                                     GValue       *return_value,
                                                                     guint         n_param_values,
                                                                     const GValue *param_values,
                                                                     gpointer      invocation_hint,
                                                                     gpointer      marshal_data);
void
dbus_glib_marshal_cd_dbus_applet_BOOLEAN__BOXED_POINTER (GClosure     *closure,
                                                         GValue       *return_value G_GNUC_UNUSED,
                                                         guint         n_param_values,
                                                         const GValue *param_values,
                                                         gpointer      invocation_hint G_GNUC_UNUSED,
                                                         gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__BOXED_POINTER) (gpointer     data1,
                                                           gpointer     arg_1,
                                                           gpointer     arg_2,
                                                           gpointer     data2);
  register GMarshalFunc_BOOLEAN__BOXED_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__BOXED_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_boxed (param_values + 1),
                       g_marshal_value_peek_pointer (param_values + 2),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:STRING,INT,POINTER (/tmp/dbus-binding-tool-c-marshallers.IISSZU:2) */
extern void dbus_glib_marshal_cd_dbus_applet_BOOLEAN__STRING_INT_POINTER (GClosure     *closure,
                                                                          GValue       *return_value,
                                                                          guint         n_param_values,
                                                                          const GValue *param_values,
                                                                          gpointer      invocation_hint,
                                                                          gpointer      marshal_data);
void
dbus_glib_marshal_cd_dbus_applet_BOOLEAN__STRING_INT_POINTER (GClosure     *closure,
                                                              GValue       *return_value G_GNUC_UNUSED,
                                                              guint         n_param_values,
                                                              const GValue *param_values,
                                                              gpointer      invocation_hint G_GNUC_UNUSED,
                                                              gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__STRING_INT_POINTER) (gpointer     data1,
                                                                gpointer     arg_1,
                                                                gint         arg_2,
                                                                gpointer     arg_3,
                                                                gpointer     data2);
  register GMarshalFunc_BOOLEAN__STRING_INT_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 4);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__STRING_INT_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_string (param_values + 1),
                       g_marshal_value_peek_int (param_values + 2),
                       g_marshal_value_peek_pointer (param_values + 3),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:STRING,POINTER (/tmp/dbus-binding-tool-c-marshallers.IISSZU:3) */
extern void dbus_glib_marshal_cd_dbus_applet_BOOLEAN__STRING_POINTER (GClosure     *closure,
                                                                      GValue       *return_value,
                                                                      guint         n_param_values,
                                                                      const GValue *param_values,
                                                                      gpointer      invocation_hint,
                                                                      gpointer      marshal_data);
void
dbus_glib_marshal_cd_dbus_applet_BOOLEAN__STRING_POINTER (GClosure     *closure,
                                                          GValue       *return_value G_GNUC_UNUSED,
                                                          guint         n_param_values,
                                                          const GValue *param_values,
                                                          gpointer      invocation_hint G_GNUC_UNUSED,
                                                          gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__STRING_POINTER) (gpointer     data1,
                                                            gpointer     arg_1,
                                                            gpointer     arg_2,
                                                            gpointer     data2);
  register GMarshalFunc_BOOLEAN__STRING_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 3);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__STRING_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_string (param_values + 1),
                       g_marshal_value_peek_pointer (param_values + 2),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

/* BOOLEAN:STRING,INT,STRING,POINTER (/tmp/dbus-binding-tool-c-marshallers.IISSZU:4) */
extern void dbus_glib_marshal_cd_dbus_applet_BOOLEAN__STRING_INT_STRING_POINTER (GClosure     *closure,
                                                                                 GValue       *return_value,
                                                                                 guint         n_param_values,
                                                                                 const GValue *param_values,
                                                                                 gpointer      invocation_hint,
                                                                                 gpointer      marshal_data);
void
dbus_glib_marshal_cd_dbus_applet_BOOLEAN__STRING_INT_STRING_POINTER (GClosure     *closure,
                                                                     GValue       *return_value G_GNUC_UNUSED,
                                                                     guint         n_param_values,
                                                                     const GValue *param_values,
                                                                     gpointer      invocation_hint G_GNUC_UNUSED,
                                                                     gpointer      marshal_data)
{
  typedef gboolean (*GMarshalFunc_BOOLEAN__STRING_INT_STRING_POINTER) (gpointer     data1,
                                                                       gpointer     arg_1,
                                                                       gint         arg_2,
                                                                       gpointer     arg_3,
                                                                       gpointer     arg_4,
                                                                       gpointer     data2);
  register GMarshalFunc_BOOLEAN__STRING_INT_STRING_POINTER callback;
  register GCClosure *cc = (GCClosure*) closure;
  register gpointer data1, data2;
  gboolean v_return;

  g_return_if_fail (return_value != NULL);
  g_return_if_fail (n_param_values == 5);

  if (G_CCLOSURE_SWAP_DATA (closure))
    {
      data1 = closure->data;
      data2 = g_value_peek_pointer (param_values + 0);
    }
  else
    {
      data1 = g_value_peek_pointer (param_values + 0);
      data2 = closure->data;
    }
  callback = (GMarshalFunc_BOOLEAN__STRING_INT_STRING_POINTER) (marshal_data ? marshal_data : cc->callback);

  v_return = callback (data1,
                       g_marshal_value_peek_string (param_values + 1),
                       g_marshal_value_peek_int (param_values + 2),
                       g_marshal_value_peek_string (param_values + 3),
                       g_marshal_value_peek_pointer (param_values + 4),
                       data2);

  g_value_set_boolean (return_value, v_return);
}

G_END_DECLS

#endif /* __dbus_glib_marshal_cd_dbus_applet_MARSHAL_H__ */

#include <dbus/dbus-glib.h>
static const DBusGMethodInfo dbus_glib_cd_dbus_applet_methods[] = {
  { (GCallback) cd_dbus_applet_set_quick_info, dbus_glib_marshal_cd_dbus_applet_BOOLEAN__STRING_POINTER, 0 },
  { (GCallback) cd_dbus_applet_set_label, dbus_glib_marshal_cd_dbus_applet_BOOLEAN__STRING_POINTER, 62 },
  { (GCallback) cd_dbus_applet_set_icon, dbus_glib_marshal_cd_dbus_applet_BOOLEAN__STRING_POINTER, 116 },
  { (GCallback) cd_dbus_applet_animate, dbus_glib_marshal_cd_dbus_applet_BOOLEAN__STRING_INT_POINTER, 169 },
  { (GCallback) cd_dbus_applet_show_dialog, dbus_glib_marshal_cd_dbus_applet_BOOLEAN__STRING_INT_POINTER, 240 },
  { (GCallback) cd_dbus_applet_populate_menu, dbus_glib_marshal_cd_dbus_applet_BOOLEAN__BOXED_POINTER, 311 },
  { (GCallback) cd_dbus_applet_add_data_renderer, dbus_glib_marshal_cd_dbus_applet_BOOLEAN__STRING_INT_STRING_POINTER, 371 },
  { (GCallback) cd_dbus_applet_render_values, dbus_glib_marshal_cd_dbus_applet_BOOLEAN__BOXED_POINTER, 456 },
  { (GCallback) cd_dbus_applet_add_sub_icons, dbus_glib_marshal_cd_dbus_applet_BOOLEAN__BOXED_POINTER, 516 },
  { (GCallback) cd_dbus_applet_remove_sub_icon, dbus_glib_marshal_cd_dbus_applet_BOOLEAN__STRING_POINTER, 579 },
};

const DBusGObjectInfo dbus_glib_cd_dbus_applet_object_info = {
  0,
  dbus_glib_cd_dbus_applet_methods,
  10,
"org.cairodock.CairoDock.applet\0SetQuickInfo\0S\0cQuickInfo\0I\0s\0\0org.cairodock.CairoDock.applet\0SetLabel\0S\0cLabel\0I\0s\0\0org.cairodock.CairoDock.applet\0SetIcon\0S\0cImage\0I\0s\0\0org.cairodock.CairoDock.applet\0Animate\0S\0cAnimation\0I\0s\0iNbRounds\0I\0i\0\0org.cairodock.CairoDock.applet\0ShowDialog\0S\0message\0I\0s\0iDuration\0I\0i\0\0org.cairodock.CairoDock.applet\0PopulateMenu\0S\0pLabels\0I\0as\0\0org.cairodock.CairoDock.applet\0AddDataRenderer\0S\0cType\0I\0s\0iNbValues\0I\0i\0cTheme\0I\0s\0\0org.cairodock.CairoDock.applet\0RenderValues\0S\0pValues\0I\0ad\0\0org.cairodock.CairoDock.applet\0AddSubIcons\0S\0pIconFields\0I\0as\0\0org.cairodock.CairoDock.applet\0RemoveSubIcon\0S\0cIconID\0I\0s\0\0\0",
"org.cairodock.CairoDock.applet\0on_click_icon\0org.cairodock.CairoDock.applet\0on_middle_click_icon\0org.cairodock.CairoDock.applet\0on_scroll_icon\0org.cairodock.CairoDock.applet\0on_build_menu\0org.cairodock.CairoDock.applet\0on_menu_select\0org.cairodock.CairoDock.applet\0on_drop_data\0org.cairodock.CairoDock.applet\0on_init_module\0org.cairodock.CairoDock.applet\0on_stop_module\0org.cairodock.CairoDock.applet\0on_reload_module\0\0",
"\0"
};

