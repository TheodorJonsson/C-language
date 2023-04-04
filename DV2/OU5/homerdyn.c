/*
 * Homer Simpson Dynamic programming
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

int not_even(int krusty, int apu, int time);
void swap(int *n, int *m);


int main(void)
{
   int krusty = 0, apu = 0, time = 0;

   while (scanf("%d %d %d", &krusty, &apu, &time) != EOF)
   {

      if(krusty > apu)
      {

         swap(&krusty, &apu);
      }

      if(time % krusty == 0)
      {
         printf("%d\n", time / krusty);
      }
      else
      {
         not_even(krusty, apu, time);
      }
   }

   return 0;
}


void swap(int *n, int *m)
{
   int temp = *n;
   *n = *m;
   *m = temp;
}


int not_even(int krusty, int apu, int time)
{
   int time_eaten = 0, amount_of_burgers = 0, i = 1, p = 0;
   int burgers[time];

   while(time_eaten < (time - krusty)) {

      time_eaten += krusty;
      burgers[amount_of_burgers] = time_eaten;
      amount_of_burgers++;
      p++;
   }

   do {

      time_eaten -= (krusty * i);
      time_eaten += apu;
      burgers[amount_of_burgers] = time_eaten;

      if(time_eaten == time) {

         printf("%d\n", amount_of_burgers);
         return 0;
      }

      amount_of_burgers--;
      i++;

      if(amount_of_burgers == 1) {

         int beer = burgers[0];

         for(int k = 0; k < p; k++) {

            if((burgers[k] < time) && (burgers[k] > burgers[k + 1])) {

               beer = burgers[k];
            }
         }

         printf("%d %d\n", beer, (time % beer));
         return 0;
      }

   } while(time_eaten > time);

   return 0;
}
