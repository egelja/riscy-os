#ifndef __KERNEL_OF_FDT_H__
#define __KERNEL_OF_FDT_H__

#include <kernel/stdint.h>
#include <kernel/string.h>

#define FDT_COMPAT_VERSION 17

#ifdef __cplusplus
extern "C" {
#endif

struct fdt {
    uint32_t magic;
    uint32_t totalsize;
    uint32_t off_dt_struct;
    uint32_t off_dt_strings;
    uint32_t off_mem_rsvmap;
    uint32_t version;
    uint32_t last_comp_version;
    uint32_t boot_cpuid_phys;
    uint32_t size_dt_strings;
    uint32_t size_dt_struct;
};

struct fdt_node {
    uint32_t token;
    char unit_name[];
};

struct fdt_prop {
    uint32_t token;
    uint32_t len;
    uint32_t name_offset;
    uint8_t val[];
};

#define FDT_BEGIN_NODE 0x1
#define FDT_END_NODE 0x2
#define FDT_PROP 0x3
#define FDT_NOP 0x4
#define FDT_END 0x9

/* --------------------
 *  CORE FUNCTIONALITY
 * -------------------- */

/*
 * Make sure that this FDT is both Valid, and a version which we are equipped to parse
 * 0 -> Valid, else Invalid
 * (FDT_COMPAT_VERSION is the version of the FDT we are targeting)
 */
int fdt_verify(struct fdt *fdt);

/*
 * Get the size of this FDT in bytes
 */
size_t fdt_size(struct fdt *fdt);

/*
 * Get the length of the value of this property in bytes
 */
size_t fdt_prop_val_len(struct fdt_prop *prop);

/*
 * Get the raw data of this property
 */
void * fdt_prop_val(struct fdt_prop *prop);

/*
 * Get the offset into the string block with the name of this property
 */
size_t fdt_prop_name_offset(struct fdt_prop *prop);

/*
 * Get the first node in the entire FDT
 */
struct fdt_node * fdt_node_begin(struct fdt *fdt);

/*
 * Returns the next node in the tree (or NULL) traversing the entire tree regardless of depth
 */
struct fdt_node * fdt_next_node(struct fdt *fdt, struct fdt_node *node);

/*
 * Returns the first property in this node (or NULL if there are none)
 */
struct fdt_prop * fdt_node_prop_begin(struct fdt *fdt, struct fdt_node *node);

/*
 * Returns the next property after this one in the same node (or NULL)
 */
struct fdt_prop * fdt_node_next_prop(struct fdt *fdt, struct fdt_prop *prop);

/*
 * Returns the first subnode of this node (or NULL if there are none)
 */
struct fdt_node * fdt_node_subnode_begin(struct fdt *fdt, struct fdt_node *node);

/*
 * Returns the next subnode after this one (or NULL)
 */
struct fdt_node * fdt_node_next_subnode(struct fdt *fdt, struct fdt_node *subnode);

/*
 * Get the string at offset "offset" in the string block
 */
const char * fdt_string_from_offset(struct fdt *fdt, size_t offset);

/*
 * Get the string representing the unit name of this node
 */
const char * fdt_node_name(struct fdt_node *node);


/* ------------------
 *  HELPER FUNCTIONS
 * ------------------ */

/*
 * Get the string representing the name of this property
 */
const char * fdt_prop_name(struct fdt *fdt, struct fdt_prop *prop);

/*
 * Find a property in "node" named "name" (or NULL if none exist)
 * The search will begin on property "start" (exclusive)
 * or if "start" is NULL, the first property in the node (inclusive)
 */
struct fdt_prop * fdt_get_prop_by_name(struct fdt *fdt, struct fdt_node *node, struct fdt_prop *start, const char *name);

/*
 * Find a node in the device tree compatible with "compat"
 * The search will begin on node "start" (exclusive)
 * or if "start" is NULL, the first node in the FDT (inclusive)
 */
struct fdt_node * fdt_find_compatible_node(struct fdt *fdt, struct fdt_node *start, const char *compat);

/*
 * Returns 1 if "node" is compatible with "compat", else 0
 */
int fdt_node_is_compatible(struct fdt *fdt, struct fdt_node *node, const char *compat); 

#ifdef __cplusplus
}
#endif

#endif
