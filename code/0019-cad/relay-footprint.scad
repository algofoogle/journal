$shell = 2;

module relay_slab(shell=0) {
  translate([-shell,-shell,0]) cube([53.1+shell*2,28.3+shell*2,1]);
}

module relay_hole(d=3.8) {
  cylinder(h=10,r1=d/2,r2=d/2,center=true,$fn=40);
}

module relay_stand(d=3.8) {
  translate([0,0,0.5-0.05]) cylinder(h=1.1,r1=d/2,r2=d/2,center=true,$fn=40);
}

module relay_pegs(fudge) {
  translate([3.2,25.1,0]) relay_hole(3.4-fudge*2);
  translate([50,25.1,0]) relay_hole(3.4-fudge*2);
  translate([50,3.2,0]) relay_hole(3.4-fudge*2);
  translate([3.3,3.3,0]) relay_hole(3.9-fudge*2);
}

module relay_footprint(shell=0,fudge=0) {
  difference() {
    relay_slab(shell+fudge);
    relay_pegs(fudge);
  }
}

module wire_hole(y,d=2.5) {
  translate([53.1+$shell/2,y+28.3/2,6.7+$shell]) rotate([0,90,0])
    cylinder(h=$shell*2,r1=d/2,r2=d/2,center=true,$fn=40);
}

// scale([1,1,2]) relay_footprint();
// translate([0,32,0]) difference() {
//   scale([1,1,20+$shell]) relay_slab($shell);
//   translate([0,0,$shell]) scale([1,1,25]) relay_footprint();
// }
// translate([0,66,0])
module relay_box() {
  color([0.7,0.7,0.7]) union() {
    difference() {
      scale([1,1,20+$shell]) relay_slab($shell);
      translate([0,0,$shell]) scale([1,1,25]) relay_footprint(0,0.2);
      wire_hole(-4.8);
      wire_hole(0);
      wire_hole(4.8);
      translate([-53.1-$shell,0,9]) hull() {
        wire_hole(-4,3);
        wire_hole(4,3);
      }
    }
    translate([0,0,$shell]) {
      scale([1,1,3]) {
        translate([3.2,25.1,0]) relay_stand(10);
        translate([50,25.1,0]) relay_stand(10);
        translate([50,3.2,0]) relay_stand(10);
        translate([3.3,3.3,0]) relay_stand(10.5);
      }
    }
  }
}

module relay_lid() {
  // translate([0,60,0])
  rotate([180,0,0]) {
    union() {
      intersection() {
        scale([1,1,25]) {
          difference() {
            relay_pegs(-1);
            scale([1,1,2]) relay_pegs(0.3);
          }
        }
        translate([0,0,3+$shell+1.4]) scale([1,1,20-3-1.4]) relay_slab();
      }
      translate([0,0,20+$shell]) scale([1,1,2]) relay_slab($shell);
    }
  }
}

relay_box();
*relay_lid();

// translate([0,40,0]) difference() {
//   translate([0,0,3+$shell+1.4]) scale([1,1,20-3-1.4]) #relay_slab();
//   relay_box();
// }