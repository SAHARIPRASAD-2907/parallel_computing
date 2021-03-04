# include <stdlib.h>
# include <stdio.h>
# include <time.h>
# include <omp.h>

# define NV 6

int main(int argc, char **argv );
int *dijkstra_distance (int ohd[NV][NV] );
void find_nearest (int s,int e,int mind[NV],int connected[NV],int *d,int *v);
void init (int ohd[NV][NV]);
void timestamp (void);
void update_mind(int s,int e,int mv,int connected[NV],int ohd[NV][NV],int mind[NV]);

/******************************************************************************/

int main (int argc,char **argv )

{
  int i;
  int i4_huge = 2147483647;
  int j;
  int *mind;
  int ohd[NV][NV];

  timestamp();
  fprintf(stdout, "\n" );
  fprintf(stdout, "DIJKSTRA_OPENMP\n" );
  fprintf(stdout, " C version\n" );
  fprintf(stdout, " Use Dijkstra's algorithm to determine the minimum\n" );
  fprintf(stdout, " distance from node 0 to each node in a graph,\n" );
  fprintf(stdout, " given the distances between each pair of nodes.\n" );
  fprintf(stdout, "\n" );
/*
  Initialize the problem data.
*/
  init (ohd);
/*
  Print the distance matrix.
*/
  fprintf(stdout,"\n");
  fprintf(stdout,"Distance matrix:\n");
  fprintf(stdout,"\n");
  for (i=0;i<NV;i++)
  {
    for (j=0;j<NV;j++ )
    {
      if (ohd[i][j]==i4_huge )
      {
        fprintf(stdout,"Inf");
      }
      else
      {
        fprintf (stdout,"%3d", ohd[i][j] );
      }
    }
    fprintf ( stdout, "\n" );
  }
/*
  Carry out the algorithm.
*/
  mind=dijkstra_distance(ohd);  
/*
  Print the results.
*/
  fprintf(stdout, "\n");
  fprintf(stdout, "  Minimum distances from node 0:\n");
  fprintf (stdout, "\n");
  for ( i = 0; i < NV; i++ )
  {
    fprintf (stdout,"%2d  %2d\n", i,mind[i]);
  }
/*
  Free memory.
*/
  free ( mind );
/*
  Terminate.
*/
  fprintf( stdout, "\n" );
  fprintf( stdout, "DIJKSTRA_OPENMP\n" );
  fprintf( stdout, "Normal end of execution.\n" );

  fprintf (stdout, "\n" );
  timestamp ();

  return 0;
}
/******************************************************************************/

int *dijkstra_distance (int ohd[NV][NV])

{
  int *connected;
  int i;
  int i4_huge = 2147483647;
  int md;
  int *mind;
  int mv;
  int my_first;
  int my_id;
  int my_last;
  int my_md;
  int my_mv;
  int my_step;
  int nth;
/*
  Start out with only node 0 connected to the tree.
*/
  connected = (int *) malloc (NV * sizeof (int));

  connected[0] = 1;
  for (i = 1;i < NV;i++)
  {
    connected[i] = 0;
  }
/*
  Initial estimate of minimum distance is the 1-step distance.
*/
  mind = (int *) malloc (NV * sizeof (int));

  for (i = 0; i < NV;i++)
  {
    mind[i] = ohd[0][i];
  }
/*
  Begin the parallel region.
*/
  # pragma omp parallel private ( my_first, my_id, my_last, my_md, my_mv, my_step ) \
  shared ( connected, md, mind, mv, nth, ohd )
  {
    my_id = omp_get_thread_num ( );
    nth = omp_get_num_threads ( ); 
    my_first = (my_id * NV ) / nth;
    my_last =((my_id + 1 )*NV)/nth - 1;

    # pragma omp single 
    {
      printf ( "\n" );
      printf ( "P%d: Parallel region begins with %d threads\n", my_id, nth );
      printf ( "\n" );
    }
    fprintf ( stdout, "  P%d:  First=%d  Last=%d\n", my_id, my_first, my_last );

    for ( my_step = 1; my_step < NV; my_step++ )
    {

      # pragma omp single //thread is run by a single avilable thread
      {
        md = i4_huge;
        mv = -1; 
      }
      find_nearest ( my_first, my_last, mind, connected, &my_md, &my_mv );

      # pragma omp critical//sectio of code is run by a single thread
      {
        if ( my_md < md )  
        {
          md = my_md;
          mv = my_mv;
        }
      }

      # pragma omp barrier//bring all the threads to syncronization point

      # pragma omp single//executing one thread at a time  
      {
        if ( mv != - 1 )
        {
          connected[mv] = 1;
          printf ( "  P%d: Connecting node %d.\n", my_id, mv );
        }
      }

      # pragma omp barrier//syncronization  point 

      if ( mv != -1 )
      {
        update_mind ( my_first, my_last, mv, connected, ohd, mind );
      }
      #pragma omp barrier//syncronization point
    }

    #pragma omp single//executing one thread at a time
    {
      printf ( "\n" );
      printf ( " P%d: Exiting parallel region.\n", my_id );
    }
  }

  free ( connected );

  return mind;
}

void find_nearest ( int s, int e, int mind[NV], int connected[NV], int *d, 
  int *v )

{
  int i;
  int i4_huge = 2147483647;

  *d = i4_huge;
  *v = -1;

  for ( i = s; i <= e; i++ )
  {
    if ( !connected[i] && ( mind[i] < *d ) )
    {
      *d = mind[i];
      *v = i;
    }
  }
  return;
}


void init ( int ohd[NV][NV] )


{
  int i;
  int i4_huge = 2147483647;
  int j;

  for ( i = 0; i < NV; i++ )  
  {
    for ( j = 0; j < NV; j++ )
    {
      if ( i == j ) 
      {
        ohd[i][i] = 0;
      }
      else
      {
        ohd[i][j] = i4_huge;
      }
    }
  }
  ohd[0][1] = ohd[1][0] = 40;
  ohd[0][2] = ohd[2][0] = 15;
  ohd[1][2] = ohd[2][1] = 20;
  ohd[1][3] = ohd[3][1] = 10;
  ohd[1][4] = ohd[4][1] = 25;
  ohd[2][3] = ohd[3][2] = 100;
  ohd[1][5] = ohd[5][1] = 6;
  ohd[4][5] = ohd[5][4] = 8;

  return;
}

void timestamp ( void )


{
# define TIME_SIZE 40

  static char time_buffer[TIME_SIZE];
  const struct tm *tm;
  time_t now;

  now = time ( NULL );
  tm = localtime ( &now );

  strftime ( time_buffer, TIME_SIZE, "%d %B %Y %I:%M:%S %p", tm );

  printf ( "%s\n", time_buffer );

  return;
# undef TIME_SIZE
}

void update_mind ( int s, int e, int mv, int connected[NV], int ohd[NV][NV],
  int mind[NV] )

{
  int i;
  int i4_huge = 2147483647;

  for ( i = s; i <= e; i++ )
  {
    if ( !connected[i] )
    {
      if ( ohd[mv][i] < i4_huge )
      {
        if ( mind[mv] + ohd[mv][i] < mind[i] )  
        {
          mind[i] = mind[mv] + ohd[mv][i];
        }
      }
    }
  }
  return;
}