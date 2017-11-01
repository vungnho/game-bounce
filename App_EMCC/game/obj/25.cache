
#include "JSON.h"
#include "StdAfx.h"

std::string file_get_contents( const char *path )
{
   FILE *file = fopen( path, "rb" );
   if ( !file )
	  return std::string("");
   fseek( file, 0, SEEK_END );
   long size = ftell( file );
   fseek( file, 0, SEEK_SET );
   std::string text;
   char *buffer = new char[size+1];
   buffer[size] = 0;
   if ( fread( buffer, 1, size, file ) == (unsigned long)size )
	  text = buffer;
   fclose( file );
   delete[] buffer;
   return text;
}

Json::Value JSONparse(std::string json)
{
	Json::Reader reader;
	Json::Value value;
    bool parsingSuccessful = reader.parse( json, value );

   if ( !parsingSuccessful )
   {
	  printf( "Failed to parse file: \n%s\n", 
			  reader.getFormatedErrorMessages().c_str() );
	  getchar();
   }

	return value;
}