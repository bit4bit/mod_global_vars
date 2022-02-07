#include <switch.h>


SWITCH_MODULE_LOAD_FUNCTION(mod_global_vars_load);
SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_global_vars_shutdown);
SWITCH_MODULE_DEFINITION(mod_global_vars, mod_global_vars_load, mod_global_vars_shutdown, NULL);

static switch_status_t load_variables_from_config(void)
{
  char *cf = "global_vars.conf";
  switch_xml_t cfg, xml, variables_tag, variable_tag;

  if (!(xml = switch_xml_open_cfg(cf, &cfg, NULL))) {
    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_ERROR, "open of %s failed\n", cf);
    return SWITCH_STATUS_TERM;
  }

  if (!(variables_tag = switch_xml_child(cfg, "variables"))) {
    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_ERROR, "Missing <variables> tag!\n");
    goto done;
  }

  for (variable_tag = switch_xml_child(variables_tag, "variable"); variable_tag; variable_tag = variable_tag->next) {
    char *vname = (char *) switch_xml_attr_soft(variable_tag, "name");
    char *vvalue = (char *) switch_xml_attr_soft(variable_tag, "value");
    switch_core_set_variable(vname, vvalue);
    switch_log_printf(SWITCH_CHANNEL_LOG, SWITCH_LOG_INFO, "global_vars set variable %s\n", vname);
  }
  
 done:
  switch_xml_free(xml);

  return SWITCH_STATUS_SUCCESS;
}

SWITCH_MODULE_LOAD_FUNCTION(mod_global_vars_load)
{
	*module_interface = switch_loadable_module_create_module_interface(pool, modname);
        if (load_variables_from_config() != SWITCH_STATUS_SUCCESS) {
          return SWITCH_STATUS_FALSE;
        }
        
	return SWITCH_STATUS_SUCCESS;
}

SWITCH_MODULE_SHUTDOWN_FUNCTION(mod_global_vars_shutdown)
{
	return SWITCH_STATUS_UNLOAD;
}

/* For Emacs:
 * Local Variables:
 * mode:c
 * indent-tabs-mode:t
 * tab-width:4
 * c-basic-offset:4
 * End:
 * For VIM:
 * vim:set softtabstop=4 shiftwidth=4 tabstop=4 noet:
 */
