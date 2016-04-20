#include "DiskTest.h"

void DiskTest() {
  int x;
  /*creat("test");
  creat("fail");*/
  exit(1);
  printf(" FAILED %d\n",creat("test"));
  creat("test");
  char* t = "The emu (Dromaius novaehollandiae) is the second-largest living bird by height, after its ratite relative, the ostrich. It is endemic to Australia where it is the largest native bird and the only extant member of the genus Dromaius. The emu's range covers most of mainland Australia, but the Tasmanian emu and King Island emu subspecies became extinct after the European settlement of Australia in 1788. The bird is sufficiently common for it to be rated as a least-concern species by the International Union for Conservation of Nature.\nEmus are soft-feathered, brown, flightless birds with long necks and legs, and can reach up to 1.9 metres (6.2 ft) in height. Emus can travel great distances, and when necessary can sprint at 50 km/h (30 mph); they forage for a variety of plants and insects, but have been known to go for weeks without eating. They drink infrequently, but take in copious amounts of water when the opportunity arises.\nBreeding takes place in May and June, and fighting among females for a mate is common. Females can mate several times and lay several clutches of eggs in one season. The male does the incubation; during this process he hardly eats or drinks and loses a significant amount of weight. The eggs hatch after around eight weeks, and the young are nurtured by their fathers. They reach full size after around six months, but can remain as a family unit until the next breeding season. The emu is an important cultural icon of Australia, appearing on the coat of arms and various coins. The bird features prominently in Indigenous Australian mythology.\nThe ostrich or common ostrich (Struthio camelus) is either one or two species of large flightless birds native to Africa, the only living member(s) of the genus Struthio, which is in the ratite family. Starting in 2014, the Somali ostrich is now considered a full species separate from the common ostrich.[3]\nThe ostrich shares the order Struthioniformes with the kiwis, emus, rheas and cassowaries. However, phylogenetic studies have shown that it is the basal extant member of Palaeognathae and is thus equally closely related to flighted tinamous.[4][5] It is distinctive in its appearance, with a long neck and legs, and can run at up to about 70 km/h (19 m/s; 43 mph),[6] the fastest land speed of any bird.[7] The ostrich is the largest living species of bird and lays the largest eggs of any living bird (extinct elephant birds of Madagascar and the giant moa of New Zealand laid larger eggs).\n The ostrich's diet consists mainly of plant matter, though it also eats invertebrates. It lives in nomadic groups of 5 to 50 birds. When threatened, the ostrich will either hide itself by lying flat against the ground, or run away. If cornered, it can attack with a kick of its powerful legs. Mating patterns differ by geographical region, but territorial males fight for a harem of two to seven females.\nThe ostrich is farmed around the world, particularly for its feathers, which are decorative and are also used as feather dusters. Its skin is used for leather products and its meat is marketed commercially, with its leanness a common marketing point.[6]";
  char* f ="The wildebeests, also called gnus or wildebai, are a genus of antelopes, Connochaetes. They belong to the family Bovidae, which includes antelopes, cattle, goats, sheep and other even-toed horned ungulates. Connochaetes includes two species, both native to Africa: the black wildebeest, or white-tailed gnu (C. gnou); and the blue wildebeest, or brindled gnu (C. taurinus). Fossil records suggest these two species diverged about one million years ago, resulting in a northern and a southern species. The blue wildebeest remained in its original range and changed very little from the ancestral species, while the black wildebeest changed more in order to adapt to its open grassland habitat in the south. The most obvious way of telling the two species apart are the differences in their colouring and in the way their horns are oriented.\nIn East Africa, the blue wildebeest is the most abundant big game species and some populations perform an annual migration to new grazing grounds but the black wildebeest is merely nomadic. Breeding in both takes place over a short period of time at the end of the rainy season and the calves are soon active and are able to move with the herd. Nevertheless, some fall prey to large carnivores. Wildebeest often graze in mixed herds with zebra which gives heightened awareness of potential predators. They are also alert to the warning signals emitted by other animals such as baboons. Wildebeest are a tourist attraction but compete with domesticated livestock for pasture and are sometimes blamed by farmers for transferring diseases and parasites to their cattle. Some illegal hunting goes on but the population trend is fairly stable and some populations are in national parks or on private land. The IUCN lists both species as being of least concern\n";
  char* l ="░░░░░▄▄▄▄▀▀▀▀▀▀▀▀▄▄▄▄▄▄░░░░░░░\n░░░░░█░░░░▒▒▒▒▒▒▒▒▒▒▒▒░░▀▀▄░░░░\n░░░░█░░░▒▒▒▒▒▒░░░░░░░░▒▒▒░░█░░░\n░░░█░░░░░░▄██▀▄▄░░░░░▄▄▄░░░░█░░\n░▄▀▒▄▄▄▒░█▀▀▀▀▄▄█░░░██▄▄█░░░░█░\n█░▒█▒▄░▀▄▄▄▀░░░░░░░░█░░░▒▒▒▒▒░█\n█░▒█░█▀▄▄░░░░░█▀░░░░▀▄░░▄▀▀▀▄▒█\n░█░▀▄░█▄░█▀▄▄░▀░▀▀░▄▄▀░░░░█░░█░\n░░█░░░▀▄▀█▄▄░█▀▀▀▄▄▄▄▀▀█▀██░█░░\n░░░█░░░░██░░▀█▄▄▄█▄▄█▄████░█░░░\n░░░░█░░░░▀▀▄░█░░░█░█▀██████░█░░\n░░░░░▀▄░░░░░▀▀▄▄▄█▄█▄█▄█▄▀░░█░░\n░░░░░░░▀▄▄░▒▒▒▒░░░░░░░░░░▒░░░█░\n░░░░░░░░░░▀▀▄▄░▒▒▒▒▒▒▒▒▒▒░░░░█░\n░░░░░░░░░░░░░░▀▄▄▄▄▄░░░░░░░░█░░";
  char* o ="░░░░░░░░░▄░░░░░░░░░░░░░░▄░░░░\n░░░░░░░░▌▒█░░░░░░░░░░░▄▀▒▌░░░\n░░░░░░░░▌▒▒█░░░░░░░░▄▀▒▒▒▐░░░\n░░░░░░░▐▄▀▒▒▀▀▀▀▄▄▄▀▒▒▒▒▒▐░░░\n░░░░░▄▄▀▒░▒▒▒▒▒▒▒▒▒█▒▒▄█▒▐░░░\n░░░▄▀▒▒▒░░░▒▒▒░░░▒▒▒▀██▀▒▌░░░\n░░▐▒▒▒▄▄▒▒▒▒░░░▒▒▒▒▒▒▒▀▄▒▒▌░░\n░░▌░░▌█▀▒▒▒▒▒▄▀█▄▒▒▒▒▒▒▒█▒▐░░\n░▐░░░▒▒▒▒▒▒▒▒▌██▀▒▒░░░▒▒▒▀▄▌░\n░▌░▒▄██▄▒▒▒▒▒▒▒▒▒░░░░░░▒▒▒▒▌░\n▀▒▀▐▄█▄█▌▄░▀▒▒░░░░░░░░░░▒▒▒▐░\n▐▒▒▐▀▐▀▒░▄▄▒▄▒▒▒▒▒▒░▒░▒░▒▒▒▒▌\n▐▒▒▒▀▀▄▄▒▒▒▄▒▒▒▒▒▒▒▒░▒░▒░▒▒▐░\n░▌▒▒▒▒▒▒▀▀▀▒▒▒▒▒▒░▒░▒░▒░▒▒▒▌░\n░▐▒▒▒▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▒▄▒▒▐░░\n░░▀▄▒▒▒▒▒▒▒▒▒▒▒░▒░▒░▒▄▒▒▒▒▌░░\n░░░░▀▄▒▒▒▒▒▒▒▒▒▒▄▄▄▀▒▒▒▒▄▀░░░\n░░░░░░▀▄▄▄▄▄▄▀▀▀▒▒▒▒▒▄▄▀░░░░░\n░░░░░░░░░▒▒▒▒▒▒▒▒▒▒▀▀░░░░░░░░\n";
  int fd;
  fd = open("new",O_RDWR);
  write(fd,l,strlen(l));
  write(fd,o,strlen(o));
  char y[strlen(l)+1];
  char z[strlen(o)+1];
  lseek(fd,0,SEEK_START);
  x=read(fd,y,strlen(l));
  int k=read(fd,z,strlen(o));
  y[x]='\0';
  z[k] ='\0';
  /*x = read(fd,y,4098);
  y[x] = '\0';
  printf("Finish %d\n",x );
  printf(y);*/
  printf(y);
  printf("\n");
  printf(z);
  while( 1 ) {
  }

  return;;
}

void (*entry_DiskTest)() = &DiskTest;
