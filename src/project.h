/*
 *      project.h - this file is part of Geany, a fast and lightweight IDE
 *
 *      Copyright 2007-2012 Enrico Tröger <enrico(dot)troeger(at)uvena(dot)de>
 *      Copyright 2007-2012 Nick Treleaven <nick(dot)treleaven(at)btinternet(dot)com>
 *
 *      This program is free software; you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation; either version 2 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License along
 *      with this program; if not, write to the Free Software Foundation, Inc.,
 *      51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 */


#ifndef GEANY_PROJECT_H
#define GEANY_PROJECT_H 1

G_BEGIN_DECLS

#define GEANY_PROJECT_EXT				"agk"

struct GeanyProjectGroup
{
	gboolean is_valid;
	gint index;
	gchar* group_name;
	gchar* full_name;
	struct GeanyProjectGroup *pParent;
	struct GeanyProject *pProject;
	GtkTreeIter iter;
};

struct GeanyProjectFile
{
	gboolean is_valid;
	gchar* file_name;
	struct GeanyProjectGroup *pParent;
	GtkTreeIter iter;
};

typedef struct GeanyProjectGroup GeanyProjectGroup;
typedef struct GeanyProjectFile GeanyProjectFile;

/** Structure for representing a project. */
typedef struct GeanyProject
{
	gboolean is_valid;
	gint index;
	gchar *name; 			/**< The name of the project. */
	gchar *description; 	/**< Short description of the project. */
	gchar *file_name; 		/**< Where the project file is stored (in UTF-8). */
	gchar *base_path;		/**< Base path of the project directory (in UTF-8, maybe relative). */
	/** Identifier whether it is a pure Geany project or modified/extended
	 * by a plugin. */
	gint type;
	
	GtkTreeIter iter;
	GPtrArray *project_files;	/**< Array of GeanyProjectFile. */
	GPtrArray *project_groups;  /**< Array of GeanyProjectGroup. */
}
GeanyProject;

extern GPtrArray *projects_array;

#define projects ((GeanyProject **)GEANY(projects_array)->pdata)
#define project_files_index(project,i) (((GeanyProjectFile **)(project)->project_files->pdata)[(i)])
#define project_groups_index(project,i) (((GeanyProjectGroup **)(project)->project_groups->pdata)[(i)])

typedef struct ProjectPrefs
{
	gchar *session_file;
	gboolean project_session;
	gboolean project_file_in_basedir;
} ProjectPrefs;

GtkWidget *project_choice;
GtkWidget *project_choice_container;

extern ProjectPrefs project_prefs;

typedef struct GlobalProjectPrefs
{
	gchar *project_file_path;
} GlobalProjectPrefs;

extern GlobalProjectPrefs global_project_prefs;


void project_init(void);

void project_finalize(void);

gint project_get_new_file_idx(GeanyProject *project);
gint project_get_new_group_idx(GeanyProject *project);

void project_new(void);

void project_open(void);

void project_import(void);

void project_export();

GeanyProject* find_project_for_document( gchar* filename );

gboolean project_close(GeanyProject *project, gboolean open_default);

gboolean project_close_all();

void project_update_list(void);

gboolean project_ask_close(void);

gboolean project_add_file(GeanyProject *project, gchar* filename, gboolean update_sidebar);

void project_remove_file(GeanyProject *project, gchar* filename, gboolean update_sidebar);

gboolean project_load_file(const gchar *locale_file_name);

gboolean project_import_from_file(const gchar *locale_file_name);

gboolean project_load_file_with_session(const gchar *file_name);

gchar *project_get_base_path(void);


const struct GeanyFilePrefs *project_get_file_prefs(void);

void project_save_prefs(GKeyFile *config);

void project_load_prefs(GKeyFile *config);

void project_setup_prefs(void);

void project_apply_prefs(void);

GeanyProject* project_find_by_filename(const gchar *filename);

GeanyProject* project_find_first_valid();

G_END_DECLS

#endif
