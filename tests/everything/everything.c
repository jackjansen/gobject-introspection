#include <string.h>
#include "everything.h"

/* basic types */
gboolean test_boolean (gboolean in)
{
  return in;
}

gint8 test_int8 (gint8 in)
{
  return in;
}

guint8 test_uint8 (guint8 in)
{
  return in;
}

gint16 test_int16 (gint16 in)
{
  return in;
}

guint16 test_uint16 (guint16 in)
{
  return in;
}

gint32 test_int32 (gint32 in)
{
  return in;
}

guint32 test_uint32 (guint32 in)
{
  return in;
}

gint64 test_int64 (gint64 in)
{
  return in;
}

guint64 test_uint64 (guint64 in)
{
  return in;
}

gint test_int (gint in)
{
  return in;
}

guint test_uint (guint in)
{
  return in;
}

glong test_long (glong in)
{
  return in;
}

gulong test_ulong (gulong in)
{
  return in;
}

gssize test_ssize (gssize in)
{
  return in;
}

gsize test_size (gsize in)
{
  return in;
}

gfloat test_float (gfloat in)
{
  return in;
}

gdouble test_double (gdouble in)
{
  return in;
}


time_t test_timet (time_t in)
{
  return in;
}

GType test_gtype (GType in)
{
  return in;
}

int test_closure (GClosure *closure)
{
  GValue return_value = {0, };
  int ret;

  g_value_init (&return_value, G_TYPE_INT);

  g_closure_invoke (closure,
                    &return_value,
                    0, NULL,
                    NULL);

  ret = g_value_get_int (&return_value);

  g_value_unset(&return_value);

  return ret;
}

int test_closure_one_arg (GClosure *closure, int arg)
{
  GValue return_value = {0, };
  GValue arguments[1];
  int ret;

  g_value_init (&return_value, G_TYPE_INT);

  memset (&arguments[0], 0, sizeof (arguments));
  g_value_init (&arguments[0], G_TYPE_INT);
  g_value_set_int (&arguments[0], arg);

  g_closure_invoke (closure,
                    &return_value,
                    1, arguments,
                    NULL);

  ret = g_value_get_int (&return_value);

  g_value_unset(&return_value);
  g_value_unset(&arguments[0]);

  return ret;
}

#if 0
/************************************************************************/
/* utf8 */
/* insert BLACK HEART SUIT to ensure UTF-8 doesn't get mangled */
static const char utf8_const[]    = "const \xe2\x99\xa5 utf8";
static const char utf8_nonconst[] = "nonconst \xe2\x99\xa5 utf8";

/** test_utf8_const_return:
 * Return value: <const char*> UTF-8 string
 */
G_CONST_RETURN char *test_utf8_const_return (void)
{
  return utf8_const;
}

/** test_utf8_nonconst_return:8
 * Return value: <char*> UTF-8 string
 */
char *test_utf8_nonconst_return (void)
{
  return g_strdup (utf8_nonconst);
}

void test_utf8_nonconst_in (char *in)
{
  g_assert (strcmp (in, utf8_nonconst) == 0);
}

void test_utf8_const_in (const char *in)
{
  g_assert (strcmp (in, utf8_const) == 0);
}

void test_utf8_out (char **out)
{
  *out = g_strdup (utf8_nonconst);
}

void test_utf8_inout (char **inout)
{
  g_assert (strcmp (*inout, utf8_const) == 0);
  *input = g_strdup (utf8_nonconst);
}
#endif

/**
 * test_filename_return:
 *
 * Return value: (element-type filename) (transfer full): list of strings
 */
GSList *test_filename_return (void)
{
  GSList *filenames = NULL;
  filenames = g_slist_prepend (filenames, g_filename_from_utf8("/etc/fstab", -1, NULL, NULL, NULL));
  filenames = g_slist_prepend (filenames, g_filename_from_utf8("åäö", -1, NULL, NULL, NULL));
  return filenames;
}

/* non-basic-types */

static const char *test_sequence[] = {"1", "2", "3"};

/* array */

/**
 * test_array_int_in:
 * @n_ints: 
 * @ints: (array length=n_ints): List of ints
 */
int
test_array_int_in (int n_ints, int *ints)
{
  int i, sum = 0;
  for (i = 0; i < n_ints; i++)
    sum += ints[i];
  return sum;
}

gboolean
test_strv_in (char **arr)
{
  if (g_strv_length (arr) != 3)
    return FALSE;
  if (strcmp (arr[0], "1") != 0)
    return FALSE;
  if (strcmp (arr[1], "2") != 0)
    return FALSE;
  if (strcmp (arr[2], "3") != 0)
    return FALSE;
  return TRUE;
}

/**
 * test_array_gtype_in:
 * @n_types: 
 * @types: (array length=n_types): List of types
 * Return value: string representation of provided types
 * */
char *
test_array_gtype_in (int n_types, GType *types)
{
  GString *string;
  int i;

  string = g_string_new ("[");
  for (i = 0; i < n_types; i++)
    {
      g_string_append (string, g_type_name (types[i]));
      g_string_append_c (string, ',');
    }
  g_string_append_c (string, ']');
  return g_string_free (string, FALSE);
}

char **
test_strv_out (void)
{
  char **ret = g_new (char *, 4);
  ret[0] = "1";
  ret[1] = "2";
  ret[2] = "3";
  ret[3] = NULL;
  return ret;
}

/* interface */

/************************************************************************/
/* GList */

static /*const*/ GList *test_sequence_list()
{
    static GList *list = NULL;
    if (!list) {
        gsize i;
        for (i = 0; i < G_N_ELEMENTS(test_sequence); ++i) {
            list = g_list_prepend (list, (gpointer)test_sequence[i]);
        }
        list = g_list_reverse (list);
    }
    return list;
}

void test_glist_free (GList *in)
{
  g_list_foreach (in, (GFunc)g_free, NULL);
  g_list_free (in);
}

/* free=none */
G_CONST_RETURN GList *test_glist_nothing_return (void)
{
  return test_sequence_list ();
}

/* free=none */
GList *test_glist_nothing_return2 (void)
{
  return test_sequence_list ();
}

/* free=g_list_free */
GList *test_glist_container_return (void)
{
  return g_list_copy (test_sequence_list ());
}

/* free=test_glist_free */
GList *test_glist_everything_return (void)
{
  GList *list;
  GList *l;

  list = g_list_copy (test_sequence_list ());
  for (l = list; l != NULL; l = l->next)
      l->data = g_strdup (l->data);
  return list;
}

static void assert_test_sequence_list (const GList *in)
{
  const GList *l;
  gsize i;

  for (i = 0, l = in; l != NULL; ++i, l = l->next)
      g_assert (strcmp (in->data, test_sequence[i]) == 0);
}

void test_glist_nothing_in (const GList *in)
{
  assert_test_sequence_list (in);
}

void test_glist_nothing_in2 (GList *in)
{
  assert_test_sequence_list (in);
}

void test_glist_container_in (GList *in)
{
  assert_test_sequence_list (in);
  g_list_free (in);
}

void test_glist_everything_in (GList *in)
{
  assert_test_sequence_list (in);
  test_glist_free (in);
}

/************************************************************************/
/* GSList */

static /*const*/ GSList *test_sequence_slist()
{
    static GSList *list = NULL;
    if (!list) {
        gsize i;
        for (i = 0; i < G_N_ELEMENTS(test_sequence); ++i) {
            list = g_slist_prepend (list, (gpointer)test_sequence[i]);
        }
        list = g_slist_reverse (list);
    }
    return list;
}

void test_gslist_free (GSList *in)
{
  g_slist_foreach (in, (GFunc)g_free, NULL);
  g_slist_free (in);
}

/* free=none */
G_CONST_RETURN GSList *test_gslist_nothing_return (void)
{
  return test_sequence_slist ();
}

/* free=none */
GSList *test_gslist_nothing_return2 (void)
{
  return test_sequence_slist ();
}

/* free=g_slist_free */
GSList *test_gslist_container_return (void)
{
  return g_slist_copy (test_sequence_slist ());
}

/* free=test_gslist_free */
GSList *test_gslist_everything_return (void)
{
  GSList *list;
  GSList *l;

  list = g_slist_copy (test_sequence_slist ());
  for (l = list; l != NULL; l = l->next)
      l->data = g_strdup (l->data);
  return list;
}

static void assert_test_sequence_slist (const GSList *in)
{
  const GSList *l;
  gsize i;

  for (i = 0, l = in; l != NULL; ++i, l = l->next)
      g_assert (strcmp (in->data, test_sequence[i]) == 0);
}

void test_gslist_nothing_in (const GSList *in)
{
  assert_test_sequence_slist (in);
}

void test_gslist_nothing_in2 (GSList *in)
{
  assert_test_sequence_slist (in);
}

void test_gslist_container_in (GSList *in)
{
  assert_test_sequence_slist (in);
  g_slist_free (in);
}

void test_gslist_everything_in (GSList *in)
{
  assert_test_sequence_slist (in);
  test_gslist_free (in);
}

/* ghash? */
/* error? */

/* enums / flags */

GType
test_enum_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GEnumValue values[] = {
            { TEST_VALUE1, "TEST_VALUE1", "value1" },
            { TEST_VALUE2, "TEST_VALUE2", "value2" },
            { TEST_VALUE3, "TEST_VALUE3", "value3" },
            { 0, NULL, NULL }
        };
        etype = g_enum_register_static (g_intern_static_string ("TestEnum"), values);
    }

    return etype;
}

GType
test_flags_get_type (void)
{
    static GType etype = 0;
    if (G_UNLIKELY(etype == 0)) {
        static const GFlagsValue values[] = {
            { TEST_FLAG1, "TEST_FLAG1", "flag1" },
            { TEST_FLAG2, "TEST_FLAG2", "flag2" },
            { TEST_FLAG3, "TEST_FLAG3", "flag2" },
            { 0, NULL, NULL }
        };
        etype = g_flags_register_static (g_intern_static_string ("TestFlags"), values);
    }

    return etype;
}

/* structures */

/**
 * test_struct_a_clone:
 * @a: the structure
 * @a_out: (out): the cloned structure
 *
 * Make a copy of a TestStructA
 */
void
test_struct_a_clone (TestStructA *a,
		     TestStructA *a_out)
{
  *a_out = *a;
}

/**
 * test_struct_b_clone:
 * @b: the structure
 * @b_out: (out): the cloned structure
 *
 * Make a copy of a TestStructB
 */
void
test_struct_b_clone (TestStructB *b,
		     TestStructB *b_out)
{
  *b_out = *b;
}

/* plain-old-data boxed types */

TestSimpleBoxedA *
test_simple_boxed_a_copy (TestSimpleBoxedA *a)
{
  TestSimpleBoxedA *new_a = g_slice_new (TestSimpleBoxedA);

  *new_a = *a;

  return new_a;
}

static void
test_simple_boxed_a_free (TestSimpleBoxedA *a)
{
  g_slice_free (TestSimpleBoxedA, a);
}

GType
test_simple_boxed_a_get_type (void)
{
  static GType our_type = 0;

  if (our_type == 0)
    our_type = g_boxed_type_register_static (g_intern_static_string ("TestSimpleBoxedA"),
					     (GBoxedCopyFunc)test_simple_boxed_a_copy,
					     (GBoxedFreeFunc)test_simple_boxed_a_free);
  return our_type;
}

TestSimpleBoxedB *
test_simple_boxed_b_copy (TestSimpleBoxedB *b)
{
  TestSimpleBoxedB *new_b = g_slice_new (TestSimpleBoxedB);

  *new_b = *b;

  return new_b;
}

gboolean
test_simple_boxed_a_equals (TestSimpleBoxedA *a,
			    TestSimpleBoxedA *other_a)
{
  return (a->some_int == other_a->some_int &&
	  a->some_int8 == other_a->some_int8 &&
	  a->some_double == other_a->some_double);
}

static void
test_simple_boxed_b_free (TestSimpleBoxedB *a)
{
  g_slice_free (TestSimpleBoxedB, a);
}

GType
test_simple_boxed_b_get_type (void)
{
  static GType our_type = 0;

  if (our_type == 0)
    our_type = g_boxed_type_register_static (g_intern_static_string ("TestSimpleBoxedB"),
					     (GBoxedCopyFunc)test_simple_boxed_b_copy,
					     (GBoxedFreeFunc)test_simple_boxed_b_free);
  return our_type;
}

/* opaque boxed */

struct _TestBoxedPrivate
{
  guint magic;
};

TestBoxed *
test_boxed_new (void)
{
  TestBoxed *boxed = g_slice_new0(TestBoxed);
  boxed->priv = g_slice_new0(TestBoxedPrivate);
  boxed->priv->magic = 0xdeadbeef;

  return boxed;
}

TestBoxed *
test_boxed_copy (TestBoxed *boxed)
{
  TestBoxed *new_boxed = test_boxed_new();
  TestBoxedPrivate *save;

  save = new_boxed->priv;
  *new_boxed = *boxed;
  new_boxed->priv = save;

  return new_boxed;
}

gboolean
test_boxed_equals (TestBoxed *boxed,
		   TestBoxed *other)
{
  return (other->some_int8 == boxed->some_int8 &&
	  test_simple_boxed_a_equals(&other->nested_a, &boxed->nested_a));
}

static void
test_boxed_free (TestBoxed *boxed)
{
  g_assert (boxed->priv->magic == 0xdeadbeef);

  g_slice_free (TestBoxedPrivate, boxed->priv);
  g_slice_free (TestBoxed, boxed);
}

GType
test_boxed_get_type (void)
{
  static GType our_type = 0;

  if (our_type == 0)
    our_type = g_boxed_type_register_static (g_intern_static_string ("TestBoxed"),
					     (GBoxedCopyFunc)test_boxed_copy,
					     (GBoxedFreeFunc)test_boxed_free);
  return our_type;
}

G_DEFINE_TYPE(TestObj, test_obj, G_TYPE_OBJECT);

static void
test_obj_class_init (TestObjClass *klass)
{
}

static void
test_obj_init (TestObj *obj)
{
}

TestObj *
test_obj_new_from_file (const char *x, GError **error)
{
  return g_object_new (TEST_TYPE_OBJ, NULL);
}

double
test_obj_static_method (int x)
{
  return x;
}