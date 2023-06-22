#include <stdio.h>
#include <malloc.h>
#define VOWELS (1u<<('a'-'a')|1u<<('e'-'a')|1u<<('i'-'a')|1u<<('o'-'a')|1u<<('u'-'a')|1u<<('y'-'a'))
#define GL_CONSONANTS (1u<<('c'-'a')|1u<<('s'-'a')|1u<<('f'-'a')|1u<<('p'-'a')|1u<<('t'-'a')|1u<<('h'-'a'))
 
unsigned int intersection_sets(unsigned int set1,unsigned int set2)
{
    set1 = set1 & set2;
    return set1;
}
 
unsigned int union_sets(unsigned int set1,unsigned int set2)
{
    set1 = set1 | set2;
    return set1;
}
 
unsigned int Not_a_set(unsigned int set)
{
    set = ~(set);
    return set;
}
 
 
int check(char* word,int length,int count)
{
    unsigned int final_set = 0;
    for(int i = 0;i < length;i++)
    {
        unsigned int set = 1u;
        int ascii_code = (int)word[i];
        if(ascii_code >= 65 && ascii_code <= 90)
        {
            ascii_code += 32;
        }
        set = set << (ascii_code - ((int)'a'));
        final_set = union_sets(set,final_set);
    }
    final_set = intersection_sets(final_set,Not_a_set(VOWELS));
    if (final_set != 0)
    {
        final_set = intersection_sets(final_set,Not_a_set(GL_CONSONANTS));
        if (final_set == 0)
        {
            printf("%s\n",word);
            count += 1;
        }
    }
    return count;
}
 
int main()
{
    char c;
    printf("Vvodite text:\n");
    c = getchar();
    char* word = NULL;
    int length = 0, count = 0;
    while(c != EOF)
    {
        int ascii_code = (int)c;
        if((ascii_code >= 65 && ascii_code <= 90)
        || (ascii_code >= 97 && ascii_code <= 122))
        {
            length += 1;
            word = (char*)realloc(word,length*sizeof(char));
            word[length-1] = c;
        }
        else if(length != 0)
        {
            count = check(word,length,count);
            length = 0;
            free(word);
            word = NULL;
        }
        c = getchar();
    }
    if(count != 0)
    {
        printf("Collichestvo slov: %d\n",count);
    }
    else
    {
        printf("Slov, soderjaschix gluxie soglasnie, net");
    }
}
