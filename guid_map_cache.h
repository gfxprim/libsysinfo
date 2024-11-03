//SPDX-License-Identifier: LGPL-2.1-or-later

/*

   Copyright (C) 2024 Cyril Hrubis <metan@ucw.cz>

 */

/**
 * @file guid_map_cache.h
 * @brief Simple UID and GID to names mapping cache.
 */
#ifndef GUID_MAP_CACHE_H
#define GUID_MAP_CACHE_H

#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <pwd.h>
#include <grp.h>

/**
 * @brief A caching ID to string ID mapping data structure.
 *
 * This is basically a very simple hash table. Since UIDs and GIDs are unique
 * and allocated in a few linear blocks we can do a very simple hashing where
 * we take last few bits from the ID and use that as a key and we will end up
 * with a reasonably distributed hash table.
 */
struct id_map {
	/** @brief Linked list of entries, in a case of a collision. */
	struct id_map *next;
	/** @brief An ID. */
	uint32_t id;
	/** @brief A name the ID maps to. */
	char name[];
};

#ifndef UID_MAP_HASH_BITS
# define UID_MAP_HASH_BITS 6
#endif
#define UID_MAP_HASH_SIZE (1<<(UID_MAP_HASH_BITS))
#define UID_MAP_HASH_FN(id) ((id) & (UID_MAP_HASH_SIZE-1))

struct id_map *uid_map[UID_MAP_HASH_SIZE];

/**
 * @brief Looks up a string user ID name based on UID number.
 *
 * @param uid An user id.
 *
 * @return An user id string or NULL if not found.
 */
static inline const char *uid_map_get(uint32_t uid)
{
	uint32_t h = UID_MAP_HASH_FN(uid);

	struct id_map *map = uid_map[h];

	while (map) {
		if (map->id == uid)
			return map->name;

		map = map->next;
	}

	struct passwd *pw = getpwuid(uid);
	if (!pw)
		return NULL;

	size_t name_len = strlen(pw->pw_name);
	struct id_map *new_map = malloc(sizeof(struct id_map) + name_len + 1);

	if (!new_map)
		return pw->pw_name;

	strcpy(new_map->name, pw->pw_name);
	new_map->id = uid;
	new_map->next = uid_map[h];
	uid_map[h] = new_map;

	return new_map->name;
}

#ifndef GID_MAP_HASH_BITS
# define GID_MAP_HASH_BITS 6
#endif
#define GID_MAP_HASH_SIZE (1<<(GID_MAP_HASH_BITS))
#define GID_MAP_HASH_FN(id) ((id) & (GID_MAP_HASH_SIZE-1))

struct id_map *gid_map[GID_MAP_HASH_SIZE];

/**
 * @brief Looks up a string group ID name based on GID number.
 *
 * @param uid An user id.
 *
 * @return An user id string or NULL if not found.
 */
static inline const char *gid_map_get(uint32_t gid)
{
	uint32_t h = GID_MAP_HASH_FN(gid);

	struct id_map *map = gid_map[h];

	while (map) {
		if (map->id == gid)
			return map->name;

		map = map->next;
	}

	struct group *gr = getgrgid(gid);
	if (!gr)
		return NULL;

	size_t name_len = strlen(gr->gr_name);
	struct id_map *new_map = malloc(sizeof(struct id_map) + name_len + 1);

	if (!new_map)
		return gr->gr_name;

	strcpy(new_map->name, gr->gr_name);
	new_map->id = gid;
	new_map->next = uid_map[h];
	gid_map[h] = new_map;

	return new_map->name;
}

static inline void id_map_drop_cache(struct id_map *map[], size_t cache_size)
{
	size_t i;

	for (i = 0; i < cache_size; i++) {
		struct id_map *n, *m = map[i];

		while (m) {
			n = m->next;
			free(m);
			m = n;
		}

		map[i] = NULL;
	}
}

static inline void uid_map_drop_cache(void)
{
	id_map_drop_cache(uid_map, UID_MAP_HASH_SIZE);
}

static inline void gid_map_drop_cache(void)
{
	id_map_drop_cache(gid_map, GID_MAP_HASH_SIZE);
}

#endif /* GUID_MAP_CACHE_H */
