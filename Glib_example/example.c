#include <glib.h>

int main(void)
{
	gboolean result;

	result = g_random_boolean();
	if( result == TRUE ){
		g_print("Heads\n");
	}
	else {
		g_print("Tails\n");
	}
	return 0;
}