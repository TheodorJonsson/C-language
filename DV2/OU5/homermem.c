/*
 * Homer Simpson Memoization
 *
 * This program will check the maximal amount of burgers Homer can eat within a
 * given time.
 *
 * Copyright 2022 Gazi Md Rakibul Hasan (ens20ghn@cs.umu.se),
 * Theodor Jonsson (ens18trn@cs.umu.se) & Simon Lindgren (dv21sln@cs.umu.se).
 * Usage requires the permission of the author.
 *
 * @author  Gazi Md Rakibul Hasan
 * @author  Theodor Jonsson
 * @author  Simon Lindgren
 * @since   2022-03-20
 *
 */

#include <stdio.h>

#define MAXSIZE 10000


int count_burgers(int krusty, int apu, int time, int *memo);
void solve(int krusty, int apu, int time, int *memo);

int largest_number(int n, int m);


int main(void)
{
  int krusty, apu, time;
  int memo[MAXSIZE];


  while(scanf("%d %d %d", &krusty, &apu, &time) != EOF)
  {
    int j = 0;
    while(j < MAXSIZE)
    {
      memo[j] = -2;
      j++;
    }
    if(krusty > time && apu > time)
    {
      printf("%d %d\n", 0, time);
    }
    else
    {
      solve(krusty, apu, time, memo);
    }

  }
  return 0;
}

void solve(int krusty, int apu, int time, int *memo)
{
  int newtime = 0, count = 0;
  count = count_burgers(krusty, apu, time, memo);
  if(count >= 0)
  {
    printf("%d\n", count);
  }
  else
  {
    newtime = time;

    do
    {
      newtime--;
      count = count_burgers(krusty, apu, newtime, memo);
    } while(count == -1);
    printf("%d %d\n", count, time - newtime);
  }
}

int count_burgers(int krusty, int apu, int time, int *memo)
{
  int krusty_count, apu_count;
  if(memo[time] != -2)
  {
    return memo[time];
  }
  if(time == 0)
  {
    memo[time] = 0;
    return memo[time];
  }
  if(time >= krusty)
  {
    krusty_count = count_burgers(krusty, apu, time - krusty, memo);
  }
  else
  {
    krusty_count = -1;
  }
  if(time >= apu)
  {
    apu_count = count_burgers(krusty, apu, time - apu, memo);
  }
  else
  {
    apu_count = -1;
  }
  if(krusty_count == -1 && apu_count == -1)
  {
    memo[time] = -1;
    return memo[time];
  }
  else
  {
    memo[time] = largest_number(krusty_count, apu_count) + 1;
    return memo[time];
  }
}

int largest_number(int n, int m)
{
  if(n < m)
  {
    return m;
  }
  else
  {
    return n;
  }
}
