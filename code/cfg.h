#ifndef _CFG_H_
#define _CFG_H_

#include "types.h"
#include "kiwi.h"
// configuration

#ifdef DEVSYS
	struct config_t { };
	struct config_setting_t { };
	
	config_setting_t *config_setting_lookup(const config_setting_t *setting, const char *path);
	config_setting_t *config_setting_get_elem(const config_setting_t *setting, u4_t index);

	int config_setting_lookup_int(const config_setting_t *setting, const char *path, int *value);
	int config_setting_lookup_float(const config_setting_t *setting, const char *path, double *value);
	int config_setting_lookup_string(const config_setting_t *setting, const char *path, const char **value);

	#define CONFIG_TYPE_INT	0
	#define CONFIG_TYPE_INT64	1
	#define CONFIG_TYPE_FLOAT	2
	#define CONFIG_TYPE_STRING	3
	#define CONFIG_TYPE_BOOL	4
	#define CONFIG_TYPE_ARRAY	5
	#define CONFIG_TYPE_LIST	6
	#define CONFIG_TYPE_GROUP	7
	int config_setting_type(const config_setting_t *setting);

	int config_setting_length(const config_setting_t *setting);
	config_setting_t *config_setting_get_member(const config_setting_t *setting, const char *path);
	const char *config_setting_name(const config_setting_t *setting);

	int config_setting_get_int(const config_setting_t *setting);
	int config_setting_get_int_elem(const config_setting_t *setting, int index);

	double config_setting_get_float(const config_setting_t *setting);
	double config_setting_get_float_elem(const config_setting_t *setting, int index);

	const char *config_setting_get_string(const config_setting_t *setting);
	const char *config_setting_get_string_elem(const config_setting_t *setting, int index);
#else
	#include <libconfig.h>
#endif

struct cfg_t {
	config_t config;
	const char *filename;
};

extern cfg_t cfg_cfg, cfg_dx;

#define CFG_NOPRINT		0x00
#define CFG_PRINT		0x01
#define CFG_REQUIRED	0x02

#define cfg_init(filename) _cfg_init(&cfg_cfg, filename)
#define cfg_int(name, val, flags) _cfg_int(&cfg_cfg, name, val, flags)
#define cfg_bool(name, val, flags) _cfg_bool(&cfg_cfg, name, val, flags)
#define cfg_string(name, val, flags) _cfg_string(&cfg_cfg, name, val, flags)
#define cfg_lookup(name, flags) _cfg_lookup(&cfg_cfg, name, flags)

#define dxcfg_init(filename) _cfg_init(&cfg_dx, filename)
#define dxcfg_int(name, val, flags) _cfg_int(&cfg_dx, name, val, flags)
#define dxcfg_bool(name, val, flags) _cfg_bool(&cfg_dx, name, val, flags)
#define dxcfg_string(name, val, flags) _cfg_string(&cfg_dx, name, val, flags)
#define dxcfg_lookup(name, flags) _cfg_lookup(&cfg_dx, name, flags)

void _cfg_init(cfg_t *cfg, const char *filename);
int _cfg_int(cfg_t *cfg, const char *name, int *val, u4_t flags);
int _cfg_bool(cfg_t *cfg, const char *name, int *val, u4_t flags);
const char *_cfg_string(cfg_t *cfg, const char *name, const char **val, u4_t flags);
config_setting_t *_cfg_lookup(cfg_t *cfg, const char *path, u4_t flags);

#endif
