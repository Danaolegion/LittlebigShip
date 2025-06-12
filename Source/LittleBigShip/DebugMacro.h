# pragma once
# include "DrawDebugHelpers.h"

#define Draw_Sphere(Location) if(GetWorld()) DrawDebugSphere(GetWorld(),Location,25,15,FColor::Red,true);
#define Draw_Sphere_SingleFrame(Location) if(GetWorld()) DrawDebugSphere(GetWorld(),Location,25,15,FColor::Red,false ,-1);
#define Draw_Line(StartLocation,EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(),Location,Location+GetActorForwardVector()*100,FColor::Blue,true);
#define Draw_Line_SingleFrame(StartLocation,EndLocation) if(GetWorld()) DrawDebugLine(GetWorld(),GetActorLocation(),GetActorLocation()+GetActorForwardVector()*100,FColor::Blue,false,-1);
#define Draw_Point(Location) if(GetWorld()) DrawDebugPoint(GetWorld(),GetActorLocation()+GetActorForwardVector()*100,10.f,FColor::Green,true);
#define Draw_Point_SingleFrame(Location) if(GetWorld()) DrawDebugPoint(GetWorld(),Location+GetActorForwardVector()*100,10.f,FColor::Green,false,-1);
#define Draw_Vector(StartLocation,EndLocation) if(GetWorld())\
{  \
DrawDebugLine(GetWorld(),Location,Location+GetActorForwardVector()*100,FColor::Blue,true);\
DrawDebugPoint(GetWorld(),Location+GetActorForwardVector()*100,10.f,FColor::Green,true);\
}
#define Draw_Vector_SingleFrame(StartLocation,EndLocation) if(GetWorld())\
{  \
DrawDebugLine(GetWorld(),GetActorLocation(),GetActorLocation()+GetActorRightVector()*400,FColor::Blue,false,-1);\
DrawDebugPoint(GetWorld(),GetActorLocation()+GetActorRightVector()*100,10.f,FColor::Green,false,-1);\
}