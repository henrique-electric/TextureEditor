
//Filters
typedef struct filters
{
    bool blur = false;
} filters;

typedef struct file_options
{
    bool save_default = false;
} file_options;

typedef struct _export_state
{
    bool open_modal = false;

    bool is_exported = false;

} export_state; 

typedef struct _editor_state
{

    // File Options
    file_options f_opt;

    // Export Options
    export_state export_st;

    // Filters
    filters filter;

} editor_state;