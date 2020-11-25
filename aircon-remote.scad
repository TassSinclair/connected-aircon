depth=43;
width=31;
height=12.8;
bottom_height=18;
wallEdge=2;
inner_width = width - wallEdge * 2;
inner_depth=depth - wallEdge * 2;

module top_box() {
    difference() {
        cube([depth, width, height]);
        translate([wallEdge, wallEdge, wallEdge]) {
            cube([inner_depth, inner_width, height]);
        }
        translate([wallEdge, 0, height - wallEdge * 2]) {
            cube([inner_depth, width, wallEdge*2]);
        }
    }
}

module temp_attachment() {
    inner_width=24;
    dht_width=16;
    width_edge=(width - inner_width) / 2;
    dht_width_edge=(width - dht_width) / 2;
    height=6;
    backing=2;
    inner_height=height - 2;
      translate([depth,0,-depth]) {
          rotate([0,-90,0]) {
             mirror([0, 0, 0]) {
                difference() {
                    cube([depth, width,height + backing]);
                    translate([wallEdge, width_edge, backing]) {
                        cube([depth, inner_width,inner_height]);
                    }
                    translate([wallEdge + 6, dht_width_edge, backing]) {
                        cube([depth, dht_width,inner_height + 5]);
                    }
                }
            }
        }
    }
}


temp_attachment();

module led_placeholder() {
    translate([-2, width/2 ,6.4]) {
        rotate([0,90,0]) {
            cylinder(d=6, h=10, $fn=20);
        }
    }
}

module wire_channel() {
    channel_width=10;
    channel_width_edge=(width - channel_width) / 2;
    channel_width_2=24;
    channel_width_edge_2=(width - channel_width_2) / 2;
    translate([depth - 12,channel_width_edge,0]) {
        cube([10, channel_width, 8]);
    }
    translate([depth - 6,channel_width_edge_2,0]) {
        cube([4, channel_width_2, 8]);
    }
}

difference() {
    top_box();
    led_placeholder(); 
    wire_channel();
}

module inside_box() {
    translate([wallEdge, wallEdge, wallEdge]) {
        // LED holder
        inset=5.3;
        inset2=7.5;
        depth=12;
        height=6;
        difference() {
            cube([depth, inner_width, height]);
            translate([0, inset, 0]) {
                cube([depth + 1, inner_width - inset * 2, 4]);
            }
            translate([0, inset2, 0]) {
                cube([depth + 1, inner_width - inset2 * 2, 7]);
            }
        }
    }
}
inside_box();

module wedge() {
    height=9;
    in=0.925;
    width=2.5;

    points=[
        [0, 0, 0], // back left bottom
        [0, width, 0], // back right bottom
        [0, width, height], // back right top
        [0, 0, height], // back left top
    
        [in, 0, 0], // front left bottom
        [in, width, 0], // front right bottom
    ];
    faces=[
        [0, 1, 2, 3], // back
        [3, 4, 0], // left
        [3, 2, 5, 4], // front
        [2, 1, 5], // right
        [0, 4, 5, 1], // bottom
    ];
    polyhedron(points, faces);
}

module bottom_box() {
    cutaway_amount=wallEdge * 1.25;
    difference() {
        translate([depth - 5.5,wallEdge * 1.5,bottom_height]) {
            cube([3, inner_width - (wallEdge), wallEdge * 2]);
        }
        translate([depth - 5.5,9,bottom_height]) {
           cube([3, 13, wallEdge * 2]);
        }
    }
    difference() {
        cube([depth, width, bottom_height]);
        translate([wallEdge, wallEdge, wallEdge]) {
            inset=7;
            cube([inner_depth - 3.5, inner_width, bottom_height]);
            translate([0, inset, 0]) {
                cube([inner_depth, inner_width - (inset * 2), bottom_height]);
            }
        }
        translate([0, 0, bottom_height - wallEdge * 2]) {
            cube([cutaway_amount, width, wallEdge * 2]);
        }

        translate([depth - cutaway_amount, 0, bottom_height - wallEdge * 2]) {
            cube([cutaway_amount, width, wallEdge * 2]);
        }
        translate([depth - 8, 10, wallEdge - 1]) {
            cube([8, width - 20, wallEdge * 3.5]);
        }
    }
}

module wedges_on_edge() {
    wedge_indentation=3;
    esp32_gap=3;
    wedge_width=2.5;
    translate([0, wedge_indentation, esp32_gap]) {
        wedge();
    }
    translate([0, inner_width - wedge_indentation - wedge_width, esp32_gap]) {
        wedge();
    }
}
    
translate([0, 50, 0]) {
//    bottom_box();
    wedge_indentation = 3;
    esp32_gap=3;
    wedge_width=2.5;
    other_side_of_the_box=-35.5;

    translate([wallEdge, wallEdge, wallEdge]) {
        difference() {
//            wedges_on_edge();
            translate([0.3, 0, 1.4]) {
//                cube([5.5, inner_width, esp32_gap]);
            }
            translate([-2, 0, bottom_height - wallEdge * 3]) {
//                cube([5.5, inner_width, 5]);
            }
        }
//        cube([5.5, inner_width, esp32_gap]);
        mirror([1,0,0]) {
            translate([other_side_of_the_box, 0, 0]) {
                difference() {
//                    wedges_on_edge();
                    translate([0.3, 0, 1.4]) {
//                        cube([5.5, inner_width, esp32_gap]);
                    }
                }
                difference() {
//                    cube([1, inner_width, esp32_gap]);
                    space=7;
                    translate([0, space, 0]) {
//                        cube([1, inner_width - space * 2, esp32_gap]);
                    }
                }
            }
        }
    }
}