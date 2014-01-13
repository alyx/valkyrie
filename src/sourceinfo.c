#include "valkyrie.h"

mowgli_heap_t *sourceinfo_heap = NULL;

static void sourceinfo_delete(sourceinfo_t *si)
{
    mowgli_heap_free(sourceinfo_heap, si);
}

sourceinfo_t *sourceinfo_create(void)
{
    sourceinfo_t *out;

    if (sourceinfo_heap == NULL)
        sourceinfo_heap = sharedheap_get(sizeof(sourceinfo_t));

    out = mowgli_heap_alloc(sourceinfo_heap);
    object_init(object(out), "<sourceinfo>", (destructor_t) sourceinfo_delete);

    return out;
}

