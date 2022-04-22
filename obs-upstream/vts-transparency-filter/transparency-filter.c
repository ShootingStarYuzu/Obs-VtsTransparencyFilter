#include <obs-module.h>
#include <graphics/vec4.h>

/* clang-format off */

#define SETTING_BACKGROUND_COLOR "background_color"
#define TEXT_BACKGROUND_COLOR    obs_module_text("BackgroundColor")

/* clang-format on */

struct vts_transparency_filter_data {
	obs_source_t *context;

	gs_effect_t *effect;

	gs_eparam_t *background_color_param;
	struct vec4 background_color;
};

static const char *vts_transparency_name(void *unused)
{
	UNUSED_PARAMETER(unused);
	return obs_module_text("VtsTransparencyFilter");
}

static void vts_transparency_update(void *data, obs_data_t *settings)
{
	struct vts_transparency_filter_data *filter = data;
	uint32_t background_color =
		(uint32_t)obs_data_get_int(settings, SETTING_BACKGROUND_COLOR);
	vec4_from_rgba(&filter->background_color, background_color | 0xFF000000);
}

static void vts_transparency_destroy(void *data)
{
	struct vts_transparency_filter_data *filter = data;

	if (filter->effect) {
		obs_enter_graphics();
		gs_effect_destroy(filter->effect);
		obs_leave_graphics();
	}

	bfree(data);
}

static void *vts_transparency_create(obs_data_t *settings, obs_source_t *context)
{
	struct vts_transparency_filter_data *filter =
		bzalloc(sizeof(struct vts_transparency_filter_data));
	char *effect_path = obs_module_file("vts_transparency_filter.effect");

	filter->context = context;

	obs_enter_graphics();

	filter->effect = gs_effect_create_from_file(effect_path, NULL);
	if (filter->effect) {
		filter->background_color_param = gs_effect_get_param_by_name(
			filter->effect, "background_color");
	}

	obs_leave_graphics();

	bfree(effect_path);

	if (!filter->effect) {
		vts_transparency_destroy(filter);
		return NULL;
	}

	vts_transparency_update(filter, settings);
	return filter;
}

static void vts_transparency_render(void *data, gs_effect_t *effect)
{
	struct vts_transparency_filter_data *filter = data;

	if (!obs_source_process_filter_begin(filter->context, GS_RGBA,
					     OBS_ALLOW_DIRECT_RENDERING))
		return;

	gs_effect_set_vec4(filter->background_color_param, &filter->background_color);

	gs_blend_state_push();
	gs_blend_function(GS_BLEND_ONE, GS_BLEND_INVSRCALPHA);

	obs_source_process_filter_end(filter->context, filter->effect, 0, 0);

	gs_blend_state_pop();

	UNUSED_PARAMETER(effect);
}

static obs_properties_t *vts_transparency_properties(void *data)
{
	obs_properties_t *props = obs_properties_create();
	obs_properties_add_color(props, SETTING_BACKGROUND_COLOR, TEXT_BACKGROUND_COLOR);
	UNUSED_PARAMETER(data);
	return props;
}

static void vts_transparency_defaults(obs_data_t *settings)
{
	obs_data_set_default_int(settings, SETTING_BACKGROUND_COLOR, 0x00FF00);
}

struct obs_source_info vts_transparency_filter = {
	.id = "vts_transparency_filter",
	.type = OBS_SOURCE_TYPE_FILTER,
	.output_flags = OBS_SOURCE_VIDEO | OBS_SOURCE_SRGB,
	.get_name = vts_transparency_name,
	.create = vts_transparency_create,
	.destroy = vts_transparency_destroy,
	.video_render = vts_transparency_render,
	.update = vts_transparency_update,
	.get_properties = vts_transparency_properties,
	.get_defaults = vts_transparency_defaults,
};

OBS_DECLARE_MODULE()
OBS_MODULE_USE_DEFAULT_LOCALE("vts-transparency-filter", "en-US")
MODULE_EXPORT const char *obs_module_description(void)
{
	return "Correction filter for semi-transparecy in VTS";
}

bool obs_module_load(void)
{
	obs_register_source(&vts_transparency_filter);
	return true;
}
