#pragma description архив спрайтов игры "Поле чудес" от Башурова (файл POLE.LIB)
#pragma endian little
#include <std/mem.pat>

u32 pal[16]={0xFF000000,0xFFAA0000,0xFF00AA00,0xFFAAAA00,0xFF0055AA,0xFFAAAAFF,0xFF55AAFF,0xFFAAAAAA,0xFF555555,0xFFFF5555,0xFF55FF55,0xFFFFFF55,0xFF5555FF,0xFFFF55FF,0xFF55FFFF,0xFFFFFFFF};
std::mem::Section IndexedData = std::mem::create_section("Indexed data");
u32 offset;

fn Decoder(u32 width, u32 height, ref u8 RawData){  
  u8 Output[width*height] @offset in IndexedData;
  u32 i=0;
  u32 n=0;
  for(u32 j=height,j>0,j-=1){
    u32 f=i+RawData[i]+(RawData[i+1]<<8)+2;
    i+=3;
    while(i<f){
      u32 k=RawData[i-1];
      if(k>127){
        u8 color=RawData[i];
        for(k-=128,k>0,k-=1){
          Output[n]=color;
          n+=1;
        }
        i+=1;
      }
      else
        for(k=k,k>0,k-=1){
          Output[n]=RawData[i];
          n+=1;
          i+=1;
        }      
      i+=1;
    }
  }
  offset+=n;
  return Output;
};

struct Row{
  u16 len;
  u8 data[len]; 
};

struct Image{
  u16 width;
  u16 height;
  padding[2];
  Row Rows[height][[no_unique_address]];
  u8  RawData[sizeof(Rows)];
  padding[128-($&127)];
 }[[hex::visualize("bitmap",Decoder(width,height,RawData),width,height,pal)]];

u8 SpritesCount @0;
u8 SpriteSizes[127] @1;
Image Sprites[SpritesCount]@128;