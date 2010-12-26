/*
 * Copyright (C) 2010 ammonkey
 *
 * This library is free software; you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License
 * version 3.0 as published by the Free Software Foundation.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License version 3.0 for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library. If not, see
 * <http://www.gnu.org/licenses/>.
 *
 * Author: ammonkey <am.monkeyd@gmail.com>
 */

#ifndef GOF_FILE_H
#define GOF_FILE_H

#include <glib.h>
#include <glib-object.h>
#include <gdk-pixbuf/gdk-pixbuf.h>
#include <gio/gio.h>
#include "nautilus-icon-info.h"

G_BEGIN_DECLS

#define GOF_TYPE_FILE (gof_file_get_type ())
#define GOF_FILE(obj) (G_TYPE_CHECK_INSTANCE_CAST ((obj), GOF_TYPE_FILE, GOFFile))
#define GOF_FILE_CLASS(klass) (G_TYPE_CHECK_CLASS_CAST ((klass), GOF_TYPE_FILE, GOFFileClass))
#define GOF_IS_FILE(obj) (G_TYPE_CHECK_INSTANCE_TYPE ((obj), GOF_TYPE_FILE))
#define GOF_IS_FILE_CLASS(klass) (G_TYPE_CHECK_CLASS_TYPE ((klass), GOF_TYPE_FILE))
#define GOF_FILE_GET_CLASS(obj) (G_TYPE_INSTANCE_GET_CLASS ((obj), GOF_TYPE_FILE, GOFFileClass))

#define _g_object_unref0(var) ((var == NULL) ? NULL : (var = (g_object_unref (var), NULL)))
#define _g_free0(var) (var = (g_free (var), NULL))

typedef struct _GOFFile GOFFile;
typedef struct _GOFFileClass GOFFileClass;
//typedef struct _GOFFilePrivate GOFFilePrivate;

struct _GOFFile {
    GObject parent_instance;
    //GOFFilePrivate * priv;
    /*gboolean selected;
      gboolean parent_directory_link;*/

    GFileInfo       *info;
    GFile           *location;
    GFile           *directory;
    const gchar     *name;
    const gchar     *display_name;
    const gchar     *ftype;
    gchar           *utf8_collation_key;
    guint64         size;
    gchar           *format_size;
    GFileType       file_type;
    gboolean        is_directory;
    gboolean        is_hidden;
    GIcon           *icon;
    GdkPixbuf       *pix;
    guint64         modified;
    gchar           *formated_modified;
    const gchar     *color;

    const gchar     *thumbnail;
    gboolean        is_thumbnailing;
};

struct _GOFFileClass {
    GObjectClass parent_class;

    /* Called when the file notices any change. */
    //void            (* changed)             (GOFFile *file);
    void            (* destroy)             (GOFFile *file);

};

/*
#define GIO_SUCKLESS_DEFAULT_ATTRIBUTES                                \
"standard::type,standard::is-hidden,standard::name,standard::display-name,standard::edit-name,standard::copy-name,standard::fast-content-type,standard::size,standard::allocated-size,access::*,mountable::*,time::*,unix::*,owner::*,selinux::*,thumbnail::*,id::filesystem,trash::orig-path,trash::deletion-date,metadata::*"
*/

#define GOF_GIO_DEFAULT_ATTRIBUTES "standard::is-hidden,standard::is-symlink,standard::type,standard::name,standard::display-name,standard::fast-content-type,standard::size,access::*,time::*"

typedef enum {
	GOF_FILE_ICON_FLAGS_NONE = 0,
	GOF_FILE_ICON_FLAGS_USE_THUMBNAILS = (1<<0)
} GOFFileIconFlags;

GType gof_file_get_type (void);

GOFFile*        gof_file_new (GFileInfo* file_info, GFile *dir);
GOFFile*        gof_file_get (GFile *location);
GFileInfo*      gof_file_get_file_info (GOFFile* self);
gint            gof_file_NameCompareFunc (GOFFile* a, GOFFile* b);
gint            gof_file_SizeCompareFunc (GOFFile* a, GOFFile* b);

int             gof_file_compare_for_sort (GOFFile *file_1,
                                           GOFFile *file_2,
                                           gint sort_type,
                                           gboolean directories_first,
                                           gboolean reversed);
GOFFile*        gof_file_ref (GOFFile *file);
void            gof_file_unref (GOFFile *file);
char *          gof_file_get_date_as_string (guint64 d);

void            gof_file_list_unref (GList *list);
void            gof_file_list_free (GList *list);
NautilusIconInfo    *gof_file_get_icon (GOFFile *file, int size, GOFFileIconFlags flags);
GdkPixbuf       *gof_file_get_icon_pixbuf (GOFFile *file, int size, gboolean force_size, GOFFileIconFlags flags);

G_END_DECLS

#endif /* GOF_DIRECTORY_ASYNC_H */
