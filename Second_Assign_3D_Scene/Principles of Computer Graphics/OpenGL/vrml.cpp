#include <stdio.h>
#include <stdlib.h>
#include <errno.h>

#include "vrml.h"
//#include "utils.h"

/* read VRML file info into two arrays for coordinate and normal vector information
   read info of indices of vectors forming polygons and corresponding normals 
*/

/* Function to test for equal strings */
bool EQUALCHARSTRINGS(char *t, char *s){
  int i = 0;
  bool equ = false;
  while (t[i] != '\0' && s[i] != '\0') {
    if (s[i] != t[i]) return false;
    i++;
  } 
  if (t[i] == '\0' && s[i] == '\0')
    return true;
  return false;
}

/* Function to read next line, skipping white spaces*/
bool ReadNextLine(FILE *fp, char *line)
{
  int i = 0;
  char c;
  c = getc(fp);
  while( c!= EOF && c!= '\n' && c!= '{' && c!= '[') {
    if (c!= ' ' && c!='\t'){
      line[i] = c;i++;}
    c = getc(fp);
  }
  if (c== EOF) return false;
  if (c == '{' || c== '[') {
    line[i] = c; i++; getc(fp);}
  line[i] = '\0';
  return true;
}

/* Actual ReadVRML file function */
int ReadVRML(const char *filename, 
             GLfloat *coordinates, GLfloat *normals, 
             GLint *indices, GLint *nindices, 
             GLint *noofpoly, int MAXSHAPES, int MAXCOORDS)    
{
  FILE    *fp;          /* Open file pointer */

  char    line[500], c;
  int     i, j, temp;
  GLfloat *coords;
  GLint   *ind, *nind;
  GLfloat *norms;

  // Try opening the file; use "rb" mode to read a binary file. 
  if ((fp = fopen(filename, "r")) == NULL)
    return 0;
  if (!ReadNextLine(fp, line)) return 0; // file is empty
  // Initialize coordinate arrays
  j=0;
  coords = coordinates;
  ind = indices;
  nind = nindices;
  norms = normals;
 
  while (ReadNextLine(fp, line)) {
    if (EQUALCHARSTRINGS(line,"point[")) {
      i=0;c=' ';
      while( c!= ']') {
        fscanf(fp,"%f %f %f",&(coords[i]), &(coords[i+1]), &coords[i+2]);
        i = i+3; c = getc(fp);
        if (c== EOF) return j+1;
      }
    }
    else  if (EQUALCHARSTRINGS(line,"Normal{") || EQUALCHARSTRINGS(line,"normalNormal{"))
    { 
      ReadNextLine(fp, line);
      c= ' ';i=0;
      while( c!= ']') {
        fscanf(fp,"%f %f %f",&(norms[i]), &(norms[i+1]), &norms[i+2]);
        i = i+3;
        c = getc(fp);
        if (c== EOF) return j+1;
      }
    } 
    else if (EQUALCHARSTRINGS(line,"coordIndex["))
    { 
      c= ' ';i=0;
      noofpoly[j] = 0;
      while( c!= ']') {
        fscanf(fp,"%d, %d, %d, %d",&(ind[i]), &(ind[i+1]), &ind[i+2], &temp);
        noofpoly[j]++;
          /* To calculate normal vectors using cross products
          GLfloat v1[3], v2[3];
          vecsub(&(coords[3*ind[i+1]]), &(coords[3*ind[i]]), v1);
          vecsub(&(coords[3*ind[i+2]]), &(coords[3*ind[i+1]]), v2);
          crossproduct(v1,v2, &norms[i]);*/
        i = i+3; c = getc(fp);
        if (c== EOF) return j+1;
        
      }
    } 
    else if (EQUALCHARSTRINGS(line,"normalIndex["))
    { 
      c= ' ';i=0;
      while( c!= ']') {
        fscanf(fp,"%d, %d, %d, %d",&(nind[i]), &(nind[i+1]), &(nind[i+2]), &temp);
        i = i+3; c = getc(fp);
        if (c== EOF) return j+1;
      }
      if(j == (MAXSHAPES-1)) return MAXSHAPES;
      j++;
      coords = coordinates+j*(3*MAXCOORDS);
      ind = indices+j*(3*MAXCOORDS);
      nind = nindices + j*(3*MAXCOORDS);
      norms = normals +j*(3*MAXCOORDS);
    }
  }
 fclose(fp);
 return j;
}
