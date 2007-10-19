/* -*- Mode: C; tab-width: 8; indent-tabs-mode: t; c-basic-offset: 8 -*-
 *
 * Copyright (C) 2007 Richard Hughes <richard@hughsie.com>
 *
 * Licensed under the GNU General Public License Version 2
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */

#ifndef __PK_BACKEND_H
#define __PK_BACKEND_H

#include <glib.h>
#include <pk-enum.h>
#include <pk-enum-list.h>
#include <pk-package-id.h>
#include <pk-debug.h>

G_BEGIN_DECLS

typedef struct _PkBackend PkBackend;
typedef struct _PkBackendDesc PkBackendDesc;

/* used by backends that implement an interface */
gboolean	 pk_backend_change_percentage		(PkBackend	*backend,
							 guint		 percentage);
gboolean	 pk_backend_change_sub_percentage	(PkBackend	*backend,
							 guint		 percentage);
gboolean	 pk_backend_change_status		(PkBackend	*backend,
							 PkStatusEnum	 status);
gboolean	 pk_backend_no_percentage_updates	(PkBackend	*backend);
gboolean	 pk_backend_finished			(PkBackend	*backend);
gboolean	 pk_backend_package			(PkBackend	*backend,
							 PkInfoEnum	 info,
							 const gchar	*package_id,
							 const gchar	*summary);
gboolean	 pk_backend_repo_detail			(PkBackend	*backend,
							 const gchar	*repo_id,
							 const gchar	*description,
							 gboolean	 enabled);
gboolean	 pk_backend_update_detail		(PkBackend	*backend,
							 const gchar	*package_id,
							 const gchar	*updates,
							 const gchar	*obsoletes,
							 const gchar	*url,
							 const gchar	*restart,
							 const gchar	*update_text);
gboolean	 pk_backend_require_restart		(PkBackend	*backend,
							 PkRestartEnum	 restart,
							 const gchar	*details);
gboolean	 pk_backend_description			(PkBackend	*backend,
							 const gchar	*package_id,
							 const gchar	*licence,
							 PkGroupEnum	 group,
							 const gchar	*description,
							 const gchar	*url,
							 gulong          size,
							 const gchar    *filelist);
gboolean	 pk_backend_error_code			(PkBackend	*backend,
							 guint		 code,
							 const gchar	*details, ...);
gboolean	 pk_backend_updates_changed		(PkBackend	*backend);
gboolean         pk_backend_repo_signature_required     (PkBackend      *backend,
							 const gchar    *repository_name,
							 const gchar    *key_url,
							 const gchar    *key_userid,
							 const gchar    *key_id,
							 const gchar    *key_fingerprint,
							 const gchar    *key_timestamp,
							 PkSigTypeEnum   type);
gboolean	 pk_backend_spawn_helper		(PkBackend	*backend,
							 const gchar	*script, ...);
gboolean	 pk_backend_change_transaction_data	(PkBackend	*backend,
							 const gchar	*data);
gboolean	 pk_backend_spawn_kill			(PkBackend	*backend);
gboolean	 pk_backend_allow_interrupt		(PkBackend	*backend,
							 gboolean	 allow_restart);
gboolean	 pk_backend_network_is_online		(PkBackend	*backend);

typedef gboolean (*PkBackendThreadFunc)			(PkBackend	*backend,
							 gpointer	 data);
gboolean	 pk_backend_thread_create		(PkBackend	*backend,
							 PkBackendThreadFunc func,
							 gpointer	 data);
gboolean	 pk_backend_thread_helper		(PkBackend	*backend,
							 PkBackendThreadFunc func,
							 gpointer	 data);

/* repo stuff */
gboolean	 pk_backend_get_repo_list		(PkBackend	*backend);
gboolean	 pk_backend_repo_enable			(PkBackend	*backend,
							 const gchar	*repo_id,
							 gboolean	 enabled);
gboolean	 pk_backend_repo_set_data		(PkBackend	*backend,
							 const gchar	*repo_id,
							 const gchar	*parameter,
							 const gchar	*value);

/**
 * PkBackendDesc:
 */
struct _PkBackendDesc {
	const char	*description;
	const char	*version;
	const char	*author;
	void		(*initialize)		(PkBackend *backend);
	void		(*destroy)		(PkBackend *backend);
	void		(*get_groups)		(PkBackend *backend, PkEnumList *elist);
	void		(*get_filters)		(PkBackend *backend, PkEnumList *elist);
	void		(*cancel)		(PkBackend *backend);
	void		(*get_depends)		(PkBackend *backend, const gchar *package_id);
	void		(*get_description)	(PkBackend *backend, const gchar *package_id);
	void		(*get_requires)		(PkBackend *backend, const gchar *package_id);
	void		(*get_update_detail)	(PkBackend *backend, const gchar *package_id);
	void		(*get_updates)		(PkBackend *backend);
	void		(*install_package)	(PkBackend *backend, const gchar *package_id);
	void		(*install_file)		(PkBackend *backend, const gchar *full_path);
	void		(*refresh_cache)	(PkBackend *backend, gboolean force);
	void		(*remove_package)	(PkBackend *backend, const gchar *package_id, gboolean allow_deps);
	void		(*resolve)		(PkBackend *backend, const gchar *filter, const gchar *package);
	void		(*rollback)		(PkBackend *backend, const gchar *transaction_id);
	void		(*search_details)	(PkBackend *backend, const gchar *filter, const gchar *search);
	void		(*search_file)		(PkBackend *backend, const gchar *filter, const gchar *search);
	void		(*search_group)		(PkBackend *backend, const gchar *filter, const gchar *search);
	void		(*search_name)		(PkBackend *backend, const gchar *filter, const gchar *search);
	void		(*update_package)	(PkBackend *backend, const gchar *package_id);
	void		(*update_system)	(PkBackend *backend);
	/* repo stuff */
	void		(*get_repo_list)	(PkBackend *backend);
	void		(*repo_enable)		(PkBackend *backend, const gchar *repo_id, gboolean enabled);
	void		(*repo_set_data)	(PkBackend *backend, const gchar *repo_id, const gchar *parameter, const gchar *value);
	gpointer	padding[12];
};

#define PK_BACKEND_OPTIONS(description, version, author, initialize, destroy, \
			   get_groups, get_filters, cancel, get_depends, get_description, \
			   get_requires, get_update_detail, get_updates, install_package, install_file, \
			   refresh_cache, remove_package, resolve, rollback, search_details, \
			   search_file, search_group, search_name, update_package, update_system, \
			   get_repo_list, repo_enable, repo_set_data) \
	G_MODULE_EXPORT const PkBackendDesc pk_backend_desc = { \
		description, \
		version, \
		author, \
		initialize, \
		destroy, \
		get_groups, \
		get_filters, \
		cancel, \
		get_depends, \
		get_description, \
		get_requires, \
		get_update_detail, \
		get_updates, \
		install_package, \
		install_file, \
		refresh_cache, \
		remove_package, \
		resolve, \
		rollback, \
		search_details, \
		search_file, \
		search_group, \
		search_name, \
		update_package, \
		update_system, \
		get_repo_list, \
		repo_enable, \
		repo_set_data, \
		{0} \
	}

G_END_DECLS

#endif /* __PK_BACKEND_H */
