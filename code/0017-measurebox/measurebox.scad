// Improve resolution of geometry:
$fs = 0.5;
$fa = 5;
$fn = 20;

// Box window dimensions, X/Y/Z:
window = [200,200,20];

// Lip is how wide the ruler edges is, extending beyond the dimensions of the window:
lip = 5;

// Shell is how thick the overall plastic frame is:
shell = 2;

// Parameters for stacking holes:
slot_hole_dia = 2;
slot_body = 6;

echo(window*2);

// Main measurebox object:
union() {
  // Cut the main frame out of a cube:
  difference() {
    cube(window+[lip*2,lip*2,0]);
    translate([lip,lip,-5]) cube(window+[0,0,10]); // -5 and 10 are arbitrary, to produce overlaps.
    translate([shell,shell,shell]) cube(window+[lip*2,lip*2,0]-[shell*2,shell*2,0]);
    // Etch out the rulers:
    union() {
      translate([lip,lip,0]) ruler(window[0], lip);
      translate([window[0],window[1],0]) translate([lip,lip,0]) rotate([0,0,180]) ruler(window[0], lip, true);
      rotate([0,0,-90]) translate([-window[0]-lip*2,0,0]) {
        translate([lip,lip,0]) ruler(window[0], lip, true);
        translate([window[0],window[1],0]) translate([lip,lip,0]) rotate([0,0,180]) ruler(window[0], lip);
      }
      // Etch the number of dots that our maximum ruler extent is at 600dpi:
      translate([window[0]+lip*1.8,window[1]+lip*1.1,-0.1])
        linear_extrude(height=shell*0.25, convexity=4)
          rotate([0,180,0]) rotate([0,0,45])
            text(str(round(200/25.4*600)), size=lip/3, font="Arial");
    }
  }
  // Create the 4 stacking holes:
  for (i = [0 :90: 360]) {
    pt = [window[0]/2+lip, window[1]/2+lip, 0];
    // Double `translate` to revolve around the centre of the box:
    //SMELL: Would be easier if the main box/cube above was all centred?
    translate(pt) rotate([0,0,i]) translate([window[0]/2+lip-shell,0,0]) slot([0,0,window[2]],90);
  }
}

// Makes a slot/hole for stacking support. Optionally uses a local position and rotation:
module slot(pos,rot) {
  offset = (slot_body-slot_hole_dia/2);
  translate(pos) rotate([0,0,rot]) translate([0,slot_body/2-slot_hole_dia,-slot_body/2]) {
    difference() {
      union() {
        translate([0,0,-slot_body/2]) cylinder(d=slot_body, h=slot_body*2, center=true);
        translate([-slot_body/2, -slot_body/2, -slot_body*1.5]) cube([slot_body, slot_body/2, slot_body*2]);
      }
      cylinder(d=slot_hole_dia, h=slot_body*2, center=true);
      translate([0,offset,-offset]) rotate([45,0,0]) cube([slot_body*4,slot_body*4,slot_body*2], center=true);
    }
  }
}

module ruler(length, depth, flip=false) {
  for (p = [0 :1: length]) {
    // 1cm marks are full length, 5mm marks are short, and 1mm marks are shortest:
    t = depth * ((p%10==0) ? 1.1 : (p%5==0) ? 0.4 : 0.2);
    //NOTE: Cube end square of 0.4mm per side means that when
    // it's rotated 45deg (to create a V-groove), it actually extends 0.4/2*sqrt(2)
    // to either side of its centre mark, i.e. about 0.283mm either side.
    // That also means that it cuts the V-groove only 0.283mm deep, which is only
    // one Z layer if printed at 0.28mm resolution. It means about 2 layers at 0.12mm,
    // or at least 3 layers if we're able to reliably print at 0.08mm. 
    translate([p,-(depth/2)*0.95,0]) {
      rotate([0,45,0]) translate([0,(depth-t)/2,0]) cube([0.4,t,0.4],center=true);
      if (p%10==0) {
        rotate([0,180,0])
          translate([1,-depth/2,-0.1]) //0.1 down to avoid CSG overlaps.
            linear_extrude(height=shell*0.25, convexity=4)
              if (flip) translate([-2,0,0]) text(flip ? str(length-p) : str(p), size=depth/2, font="Arial", halign="right");
              else text(flip ? str(length-p) : str(p), size=depth/2, font="Arial");
      }
    }
    //NOTE: Depth 1.1 and 0.95 factors are to ensure there's overlap which in turn
    // helps ensure a clean CSG difference.
  }
}

// Old example code below that I will use later to implement text:

// // logo_and_text.scad - Example for use<> and text()

// use <logo.scad> // Imports the Logo() module from logo.scad into this namespace

// // Set the initial viewport parameters
// $vpr = [90, 0, 0];
// $vpt = [250, 0, 80];
// $vpd = 500;

// logosize = 120;


// translate([110, 0, 80]) {
//   translate([0, 0, 30]) rotate([25, 25, -40]) Logo(logosize);
//   translate([100, 0, 40]) green() t("Open", 42, ":style=Bold");
//   translate([247, 0, 40]) black() t("SCAD", 42, ":style=Bold");
//   translate([100, 0, 0]) black() t("The Programmers");
//   translate([160, 0, -30]) black() t("Solid 3D CAD Modeller");
// }

// // Helper to create 3D text with correct font and orientation
// module t(t, s = 18, style = "") {
//   rotate([90, 0, 0])
//     linear_extrude(height = 1)
//       text(t, size = s, font = str("Liberation Sans", style), $fn = 16);
// }

// // Color helpers
// module green() color([81/255, 142/255, 4/255]) children();
// module black() color([0, 0, 0]) children();

