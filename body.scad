$fa=1;$fs=.5;

body_size=[70,70];
body_height=23;
body_r=15;
body_bevel=2;
body_bevel_angle=60;


module rsq(size=[50,50],r=10){
	minkowski(){square([size[0]-2*r,size[1]-2*r],center=true);circle(r=r);}
}
module panel(size=[50,50],r=10,bevel=2,thick=3,bevel_angle=60){
	assert(bevel<=thick);
	assert(bevel<=r);
	minkowski(){
		linear_extrude(max(thick-bevel,.001))square([size[0]-2*r,size[1]-2*r],center=true);
		cylinder(bevel,r-bevel/tan(bevel_angle),r);
	}
}
//panel(body_size,body_r,body_bevel,3,body_bevel_angle);
linear_extrude(body_height)rsq(body_size);
