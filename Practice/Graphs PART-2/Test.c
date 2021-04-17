#include <stdio.h>

#include <stdlib.h>

#include <string.h>

#include "ListGraph.h"

#include "Queue.h"

#include "Stack.h"

#include "utils.h"

#define level color
#define MAX_NODES 100
#define INF - 1

/**
 * Adaugati nodurile componentei conexe curente in lista component. 
 */
static void
dfs_connected_comps(list_graph_t * lg, int node, int * visited, linked_list_t * component) {
    stack_t * mystack = st_create(sizeof(int));
    st_push(mystack, & node);
    visited[node] = 1;
    ll_add_nth_node(component, component -> size, & node);

    while (!st_is_empty(mystack)) {
        int v = * ((int * ) st_peek(mystack));

        int found = -1;
        int data = 0;
        ll_node_t * newnode = lg -> neighbors[v] -> head;
        for (int i = 0; i < (int) lg -> neighbors[v] -> size; i++) {
            data = * ((int * ) newnode -> data);
            if (visited[data] == 0) {
                found = data;
                break;
            }
            newnode = newnode -> next;
        }

        if (found >= 0) {
            visited[found] = 1;
            st_push(mystack, & found);
            int index = -1;
            ll_node_t * mynew = component -> head;
            for (int i = 0; i < (int) component -> size; i++) {
                int my_val = * ((int * ) mynew -> data);
                if (my_val > found) {
                    index = i;
                    break;
                }
                mynew = mynew -> next;
            }
            if (index != -1)
                ll_add_nth_node(component, index, & found);
            else
                ll_add_nth_node(component, component -> size, & found);
        } else {

            st_pop(mystack);
        }
    }
    st_free(mystack);
}

static linked_list_t **
connected_components(list_graph_t * lg, int * visited, unsigned int * num_comp) {
        linked_list_t ** componente_conexe = malloc((lg -> nodes) * sizeof(linked_list_t * ));
        DIE(!componente_conexe, "malloc comps failed");

        for (int i = 0; i < lg -> nodes; i++) {
            componente_conexe[i] = ll_create(sizeof(int));
        }

        * num_comp = 0;
        for (int i = 0; i < lg -> nodes; i++) {
            if (visited[i] == 0) {
                dfs_connected_comps(lg, i, visited, componente_conexe[ * num_comp]);
                * num_comp = * num_comp + 1;
            }
        }

        return componente_conexe;
    }

static void
dfs_topo_sort(list_graph_t * lg, int node, int * visited, linked_list_t * sorted) {
    stack_t * mystack = st_create(sizeof(int));
    st_push(mystack, & node);
    visited[node] = 1;
    while (!st_is_empty(mystack)) {
        int v = * ((int * ) st_peek_new(mystack));
        int found = -1;
        int data = 0;
        ll_node_t * newnode = lg -> neighbors[v] -> head;
        for (int i = 0; i < (int) lg -> neighbors[v] -> size; i++) {
            data = * ((int * ) newnode -> data);
            if (visited[data] == 0) {
                found = data;
                break;
            }
            newnode = newnode -> next;
        }
        if (found != -1) {
            visited[found] = 1;
            st_push(mystack, & found);
        } else {
            int source = * ((int * )(st_peek_new(mystack)));
            ll_add_nth_node(sorted, 0, & source);
            st_pop_new(mystack);
        }
    }
    st_free(mystack);
}

static linked_list_t *topo_sort(list_graph_t * lg, int * visited) {
        linked_list_t * sorted = ll_create(sizeof(int));

        for (int i = 0; i < (int) lg -> nodes; i++) {
            visited[i] = 0;
        }
        /* TODO: adaugati nodurile in lista sorted, in ordinea corecta */
        for (int i = 0; i < lg -> nodes - 1; i++) {
            if (visited[i] == 0) {
                dfs_topo_sort(lg, i, visited, sorted);
            }
        }

        return sorted;
    }

static void
min_path(list_graph_t * lg, int start, int * dist) {
    if (!lg)
        return;

    int visited[MAX_NODES];
    for (int i = 0; i < MAX_NODES; i++)
        visited[i] = 0;

    queue_t * my_queue = q_create(sizeof(int), MAX_NODES);
    q_enqueue(my_queue, & start);
    dist[start] = 0;
    visited[start] = 1;

    while (!q_is_empty(my_queue)) {
        int v = * ((int * )(q_front(my_queue)));
        q_dequeue(my_queue);

        // Luam vecinii
        linked_list_t * mylist = ll_create(sizeof(int));
        ll_node_t * mynode = lg -> neighbors[v] -> head;
        for (int i = 0; i < (int) lg -> neighbors[v] -> size; i++) {
            ll_add_nth_node(mylist, mylist -> size, mynode -> data);
            mynode = mynode -> next;
        }

        // Parcurgem vecinii
        mynode = mylist -> head;
        for (int i = 0; i < (int) mylist -> size; i++) {
            int data = * ((int * )(mynode -> data));
            if (visited[data] == 0) {
                visited[data] = 1;
                dist[data] = dist[v] + 1;
                q_enqueue(my_queue, & data);
            }
            mynode = mynode -> next;
        }
        ll_free(&mylist);
    }
    q_free(my_queue);
}

static int
check_bipartite(list_graph_t * lg, int * level) {
    if (!lg)
        return 0;

    int visited[lg -> nodes];
    for (int i = 0; i < lg -> nodes; i++) {
        level[i] = 0;
        visited[i] = 0;
    }

    queue_t * my_queue = q_create(sizeof(int), lg -> nodes);
    int starting_node = 0;
    level[starting_node] = 2;
    q_enqueue(my_queue, & starting_node);
    visited[starting_node] = 1;

    while (!q_is_empty(my_queue)) {
        int v = * ((int * )(q_front(my_queue)));
        q_dequeue(my_queue);

        // Luam vecinii
        linked_list_t * mylist = ll_create(sizeof(int));
        ll_node_t * mynode = lg -> neighbors[v] -> head;
        for (int i = 0; i < (int) lg -> neighbors[v] -> size; i++) {
            ll_add_nth_node(mylist, mylist -> size, mynode -> data);
            mynode = mynode -> next;
        }

        // Parcurgem vecinii
        mynode = mylist -> head;
        for (int i = 0; i < (int) mylist -> size; i++) {
            int data = * ((int * )(mynode -> data));
            if (visited[data] == 0) {
                if (level[data] == 0) {
                    if (level[v] == 2)
                        level[data] = 1;
                    else
                        level[data] = 2;
                    q_enqueue(my_queue, & data);
                    visited[data] = 1;
                } else {
                    return 0;
                }
            }
            mynode = mynode -> next;
        }
        ll_free(&mylist);
    }

    q_free(my_queue);
    return 1;
}

static void
test_connected_comp(FILE * fptr) {
    unsigned int num_comps = 0, i = 0, nodes = 0, edges = 0;
    int x, y;
    int visited[MAX_NODES];
    for (int i = 0; i < MAX_NODES; i++)
        visited[i] = 0;
    list_graph_t * lg = NULL;
    linked_list_t ** comps = {
        NULL
    };
    printf("UNDIRECTED graph for the connected components problem:\n");
    fscanf(fptr, "%u %u", & nodes, & edges);
    lg = lg_create(nodes);

    for (i = 0; i != edges; ++i) {
        fscanf(fptr, "%d %d", & x, & y);
        lg_add_edge(lg, x, y);
        lg_add_edge(lg, y, x);
    }

    comps = connected_components(lg, visited, & num_comps);

    printf("Found %d connected components:\n", num_comps);
    for (i = 0; i != num_comps; ++i) {
        ll_print_int(comps[i]);
        ll_free(comps + i);
    }
    for(int i=num_comps;i<lg->nodes;i++) {
      ll_free(&comps[i]);
    }
    printf("\n");
    free(comps);
    lg_free(lg);
}

static void
test_topo_sort(FILE * fptr) {
    unsigned int i = 0, nodes = 0, edges = 0;
    int x = 0, y = 0;
    int visited[MAX_NODES] = {
        0
    };
    list_graph_t * lg = NULL;
    linked_list_t * sorted = NULL;

    printf("DIRECTED graph for the topological sort problem:\n");
    fscanf(fptr, "%u %u", & nodes, & edges);
    lg = lg_create(nodes);

    for (i = 0; i != edges; ++i) {
        fscanf(fptr, "%d %d", & x, & y);
        lg_add_edge(lg, x, y);
    }

    print_lg(lg);
    sorted = topo_sort(lg, visited);

    printf("Topologically sorted nodes:\n");
    ll_print_int(sorted);
    printf("\n");

    ll_free( & sorted);
    lg_free(lg);
}

static void
test_min_dist(FILE * fptr) {
    unsigned int nodes = 0, edges = 0, time = 0;
    int i;
    int x = 0, y = 0;
    int dist[MAX_NODES] = {
        0
    };
    list_graph_t * lg = NULL;

    printf("UNDIRECTED graph for the minimum distance problem:\n");
    fscanf(fptr, "%u %u %u", & nodes, & edges, & time);
    lg = lg_create(nodes);

    for (i = 0; i != (int)(edges + 1); ++i) {
        fscanf(fptr, "%d %d", & x, & y);
        lg_add_edge(lg, x, y);
        lg_add_edge(lg, y, x);
    }
    // print_lg(lg);

    for (i = 0; i != (int) nodes; ++i)
        dist[i] = INF;

    min_path(lg, 0, dist);
    for (int i = 0; i != (int) nodes; i++)
        dist[i] = dist[i] * time;

    printf("Minimum distances to node 0:\n");
    for (i = 0; i != (int) nodes; ++i)
        printf("%u: %d\n", i, dist[i]);
    printf("\n");

    lg_free(lg);
}

static void
test_bipartite(FILE * fptr) {
    unsigned int i = 0, nodes = 0, edges = 0;
    int color[MAX_NODES] = {
        0
    };
    int x, y;
    list_graph_t * lg;

    printf("UNDIRECTED graph for the bipartite graph problem:\n");
    fscanf(fptr, "%u %u", & nodes, & edges);
    lg = lg_create(nodes);

    for (i = 0; i != edges; ++i) {
        fscanf(fptr, "%d %d", & x, & y);
        lg_add_edge(lg, x, y);
        lg_add_edge(lg, y, x);
    }

    if (check_bipartite(lg, color)) {
        printf("Nodes with colour 1:\n");
        for (int i = 0; i < lg -> nodes; ++i)
            if (color[i] == 1)
                printf("%d ", i);
        printf("\nNodes with colour 2:\n");
        for (int i = 0; i < lg -> nodes; ++i)
            if (color[i] == 2)
                printf("%d ", i);
        printf("\n");
    } else
        printf("The graph is not bipartite\n");

    lg_free(lg);
}

// Verifica daca un nod se afla in lant
int nouInLant(linked_list_t * lant, int value) {
    ll_node_t * mynode = lant -> head;
    for (int i = 0; i < (int) lant -> size; i++) {
        int node_data = * ((int * ) mynode -> data);
        if (node_data == value)
            return 0;
        mynode = mynode -> next;
    }
    return 1;
}

// Construire lant
// 3 1 4 2 0
int construireLant(linked_list_t * lant, int nr_nodes, list_graph_t * graph, int * node_list) {
    if ((int) lant -> size == nr_nodes) {
        int beginning = * ((int * ) lant -> head -> data);
        int end = ll_get_last(lant);

        if (lg_has_edge(graph, beginning, end))
            return 1;
    } else {
        for (int i = 0; i < nr_nodes; i++) {
            int end = ll_get_last(lant);

            if (lg_has_edge(graph, node_list[i], end) == 1 && nouInLant(lant, node_list[i]) == 1) {
                ll_add_nth_node(lant, lant -> size, & node_list[i]);

                // If we want to find all hemiltonian cycles
                // we replace the if statement bellow with just:
                // construireLant(lant,nr_nodes,graph,node_list);
                if (construireLant(lant, nr_nodes, graph, node_list) == 1)
                    return 1;
                ll_node_t* my_node = ll_remove_nth_node(lant, lant -> size - 1);
                free(my_node->data);
                my_node->data  = NULL;
                my_node->next = NULL;
                free(my_node);
                my_node = NULL;
            }
        }
    }
    
    return 0;
}

int in_vect(int * node_list, int data, int nr_nodes) {
    for (int i = 0; i < nr_nodes; i++)
        if (data == node_list[i])
            return 1;

    return 0;
}

void test_hamilton(FILE * fptr) {
    // Create list
    printf("\nUNDIRECTED graph for the hamilton graph problem:\n");
    list_graph_t * my_graph = NULL;

    // Get nodes and edges
    int nodes = 0, edges = 0;
    fscanf(fptr, "%d %d", & nodes, & edges);
    my_graph = lg_create(nodes);
    DIE(!my_graph, "Error creating list!\n");

    // Create graph
    int val1 = 0, val2 = 0;
    for (int i = 0; i < edges; i++) {
        fscanf(fptr, "%d %d", & val1, & val2);
        lg_add_edge(my_graph, val1, val2);
        lg_add_edge(my_graph, val2, val1);
    }

    int node_list[nodes];
    for (int i = 0; i < nodes; i++)
        node_list[i] = -1;
    // Create node list
    int cnt = 0;

    for (int i = 0; i < my_graph -> nodes; i++) {
        ll_node_t * mynode = my_graph -> neighbors[i] -> head;
        if (mynode) {
            for (int j = 0; j < (int) my_graph -> neighbors[i] -> size; j++) {
                int data = * ((int * ) mynode -> data);
                if (in_vect(node_list, data, nodes) == 0) {
                    node_list[cnt++] = data;
                }
                mynode = mynode -> next;
            }
        }
    }
    // print_lg(my_graph);
    linked_list_t * lant = NULL;
    lant = ll_create(sizeof(int));
    int start = 0;
    ll_add_nth_node(lant, 0, & start);
    if (construireLant(lant, nodes, my_graph, node_list) == 1)
        printf("HAMILTONIAN CYCLE!\n");
    else
        printf("NON-HAMILTONIAN CYCLE!\n");
      
    lg_free(my_graph);
    ll_free(&lant);
}

int main(void) {

    FILE * fptr = NULL;
    fptr = fopen("InputFile.txt", "rt");
    DIE(!fptr, "Couldn't open file! Please check that the input file is in the same folder!!!\n");
    /* 1) [3.5p]Într-o rețea de socializare pentru gameri există mai multe clanuri.
    	Doi jucători fac parte din același clan dacă există un drum atât de la X la Y, cât și de la Y la X.
    	Când se creează o nouă legatură între doi jucători, clanurile din care ei fac parte se unesc formând un singur clan.

    	Se dau n numărul de gameri din rețeaua de socializare si m numărul de legături ce există intre aceștia.
    	În continuare, sunt citite cele m legături.

    	Determinați numărul clanurilor existente în rețea și jucătorii care fac parte din fiecare clan,
    	completând metodele connected_components și dfs_connected_comps din schelet.
    */
    /* INPUT OCW
    12 10 
    0 1 
    0 2 
    1 2 
    2 3 
    4 5 
    4 6 
    5 6 
    4 7 
    7 8 
    9 10 
    */
    test_connected_comp(fptr);

    /* 2) [3.5p] Un curier, care se află într-un oraș A, trebuie să livreze un pachet într-un oraș B.

    	Pe hartă se află n orașe, conectate prin m străzi bidirecționale.
    	Se știe faptul că fiecare dintre aceste străzi este parcursă într-un timp constant t.

    	Se citesc n, m, numărul de teste, cele m străzi și un număr de perechi de orașe A și B egal cu numărul de teste.

    	Determinați ruta cea mai scurtă pe care poate ajunge curierul în orașul B,
    	în cazul în care aceasta există, completând metoda min_path din schelet.
    */
    /* INPUT OCW
    7 10 1
    0 1 
    0 4 
    1 2 
    1 3 
    1 4 
    2 4 
    3 5 
    3 6 
    4 5 
    4 6 
    0 6 
    */
    test_min_dist(fptr);

    /*
3)[3.5p] În primii ani de studiu, toți studenții de la Facultatea de Automatică și Calculatoare studiază un număr de N materii obligatorii.
	Dându-se un set de relații între acestea, cu semnificația că materia din stânga trebuie studiată într-un semestru anterior (nu neapărat din același an),
	celei din partea dreaptă, găsiti și implementați un algoritm care propune o ordine corectă de studiere a materiilor universitare,
	care să respecte restricțiile impuse, completând metodele topo_sort și dfs_topo_sort din schelet.
*/

    /* INPUT OCW */
    /*
    6 4 
    Programarea_Calculatoarelor  Structuri_de_Date 
    Structuri_de_Date Programare_Orientata_pe_Obiecte 
    Matematica1  Fizica 
    Matematica2  Fizica 

    OUTPUT:
    Matematica2 
    Matematica1 
    Fizica 
    Programarea_Calculatoarelor 
    Structuri_de_Date 
    Programare_Orientata_pe_Obiecte 
    =====

    6 4
    3 4  PC SD
    4 5  SD POO
    0 2  M1 FIZ
    1 2	 M2 FIZ
    */

    test_topo_sort(fptr);

    /* Ex 4 */
    /*
  4) [3.5p] Dându-se n noduri și m muchii ale unui graf neorientat,
  determinați dacă acest graf este bipartit și aflați cele două mulțimi care îl formează,
  completând metoda check_bipartite din schelet.

  INPUT:
  9 8 
  0 1 
  0 6 
  1 2 
  2 7 
  3 6 
  4 7 
  4 8 
  5 8 

  EXPECTED OUTPUT:
  0 2 3 4 5 
  1 6 7 8 
    */
    test_bipartite(fptr);
    /*
    [2p] Un curier trebuie să livreze pachete în n orașe. Orașele sunt codificate prin numere de la 0 la n-1.
    Se cunosc m străzi bidirecționale, legături între orașe. Se citesc numarul de teste,
    apoi pentru fiecare test n, m și cele m străzi bidirecționale.
    Sediul curieratului se află în orașul 0. Determinați toate rutele pe care curierul
    le poate urma astfel încât acesta să efectueze toate livrările și să se întoarcă la sediu,
    astfel încât el va trece prin fiecare oras o singură data.
    INPUT:
    5 7 
    0 1 
    1 2 
    0 3 
    1 3 
    1 4 
    2 4 
    3 4
    OUTPUT EXPECTED: 0 1 2 4 3 0 
    */

    test_hamilton(fptr);


    fclose(fptr);
    return 0;
}