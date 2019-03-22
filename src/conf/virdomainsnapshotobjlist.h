/*
 * virdomainsnapshotobjlist.h: handle a tree of snapshot objects
 *                  (derived from snapshot_conf.h)
 *
 * Copyright (C) 2006-2019 Red Hat, Inc.
 * Copyright (C) 2006-2008 Daniel P. Berrange
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library.  If not, see
 * <http://www.gnu.org/licenses/>.
 */

#ifndef LIBVIRT_VIRDOMAINSNAPSHOTOBJLIST_H
# define LIBVIRT_VIRDOMAINSNAPSHOTOBJLIST_H

# include "internal.h"
# include "virdomainsnapshotobj.h"
# include "virbuffer.h"

/* Filter that returns true if a given snapshot matches the filter flags */
typedef bool (*virDomainSnapshotObjListFilter)(virDomainSnapshotObjPtr obj,
                                               unsigned int flags);

virDomainSnapshotObjListPtr virDomainSnapshotObjListNew(void);
void virDomainSnapshotObjListFree(virDomainSnapshotObjListPtr snapshots);

int virDomainSnapshotObjListParse(const char *xmlStr,
                                  const unsigned char *domain_uuid,
                                  virDomainSnapshotObjListPtr snapshots,
                                  virCapsPtr caps,
                                  virDomainXMLOptionPtr xmlopt,
                                  unsigned int flags);
int virDomainSnapshotObjListFormat(virBufferPtr buf,
                                   const char *uuidstr,
                                   virDomainSnapshotObjListPtr snapshots,
                                   virCapsPtr caps,
                                   virDomainXMLOptionPtr xmlopt,
                                   unsigned int flags);

virDomainSnapshotObjPtr virDomainSnapshotAssignDef(virDomainSnapshotObjListPtr snapshots,
                                                   virDomainSnapshotDefPtr def);

int virDomainSnapshotObjListGetNames(virDomainSnapshotObjListPtr snapshots,
                                     virDomainSnapshotObjPtr from,
                                     char **const names, int maxnames,
                                     unsigned int flags);
int virDomainSnapshotObjListNum(virDomainSnapshotObjListPtr snapshots,
                                virDomainSnapshotObjPtr from,
                                unsigned int flags);
virDomainSnapshotObjPtr virDomainSnapshotFindByName(virDomainSnapshotObjListPtr snapshots,
                                                    const char *name);
int virDomainSnapshotObjListSize(virDomainSnapshotObjListPtr snapshots);
virDomainSnapshotObjPtr virDomainSnapshotGetCurrent(virDomainSnapshotObjListPtr snapshots);
const char *virDomainSnapshotGetCurrentName(virDomainSnapshotObjListPtr snapshots);
bool virDomainSnapshotIsCurrentName(virDomainSnapshotObjListPtr snapshots,
                                    const char *name);
void virDomainSnapshotSetCurrent(virDomainSnapshotObjListPtr snapshots,
                                 virDomainSnapshotObjPtr snapshot);
bool virDomainSnapshotObjListRemove(virDomainSnapshotObjListPtr snapshots,
                                    virDomainSnapshotObjPtr snapshot);
void virDomainSnapshotObjListRemoveAll(virDomainSnapshotObjListPtr snapshots);
int virDomainSnapshotForEach(virDomainSnapshotObjListPtr snapshots,
                             virHashIterator iter,
                             void *data);
int virDomainSnapshotUpdateRelations(virDomainSnapshotObjListPtr snapshots);

# define VIR_DOMAIN_SNAPSHOT_FILTERS_METADATA \
               (VIR_DOMAIN_SNAPSHOT_LIST_METADATA     | \
                VIR_DOMAIN_SNAPSHOT_LIST_NO_METADATA)

# define VIR_DOMAIN_SNAPSHOT_FILTERS_LEAVES \
               (VIR_DOMAIN_SNAPSHOT_LIST_LEAVES       | \
                VIR_DOMAIN_SNAPSHOT_LIST_NO_LEAVES)

# define VIR_DOMAIN_SNAPSHOT_FILTERS_STATUS \
               (VIR_DOMAIN_SNAPSHOT_LIST_INACTIVE     | \
                VIR_DOMAIN_SNAPSHOT_LIST_ACTIVE       | \
                VIR_DOMAIN_SNAPSHOT_LIST_DISK_ONLY)

# define VIR_DOMAIN_SNAPSHOT_FILTERS_LOCATION \
               (VIR_DOMAIN_SNAPSHOT_LIST_INTERNAL     | \
                VIR_DOMAIN_SNAPSHOT_LIST_EXTERNAL)

# define VIR_DOMAIN_SNAPSHOT_FILTERS_ALL \
               (VIR_DOMAIN_SNAPSHOT_FILTERS_METADATA  | \
                VIR_DOMAIN_SNAPSHOT_FILTERS_LEAVES    | \
                VIR_DOMAIN_SNAPSHOT_FILTERS_STATUS    | \
                VIR_DOMAIN_SNAPSHOT_FILTERS_LOCATION)

int virDomainListSnapshots(virDomainSnapshotObjListPtr snapshots,
                           virDomainSnapshotObjPtr from,
                           virDomainPtr dom,
                           virDomainSnapshotPtr **snaps,
                           unsigned int flags);

/* Access the snapshot-specific definition from a given list member. */
static inline virDomainSnapshotDefPtr
virDomainSnapshotObjGetDef(virDomainSnapshotObjPtr obj)
{
    return (virDomainSnapshotDefPtr) obj->def;
}

#endif /* LIBVIRT_VIRDOMAINSNAPSHOTOBJLIST_H */
