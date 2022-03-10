var packageName;
var m_pkg = "16-10582";
var tot;
var test0;

function draw_canvas3(VLSI) {
    var canvas = document.querySelector('canvas');
    // 目前思路：最终传入绘图函数的会是这样一个数据：Object{ Location:[[], [], [], []], Type: ,Format}
    var c = canvas.getContext('2d');
    // js supports string -> float
    var test_data;
    var con_data;
    var modify_x = 10000;
    var modify_y = 10000;
    var max_x = -2000;
    var max_y = -2000;
    /**
     * adjust canvas size
     * @param {*} x_min 
     * @param {*} x_max 
     * @param {*} y_min 
     * @param {*} y_max 
     */
    function resize_canvas(x_min, x_max, y_min, y_max) {
        canvas.width = ((x_max - x_min) + 1) * 2;
        canvas.height = ((y_max - y_min) + 1) * 2;
    }

    function draw_canvas2(target) {
        if (target.Format == "Border") {
            c.lineWidth = 1.1;
        }
        else {
            c.lineWidth = 1;
        }
        let detail_route = target.Location;

        if (target.Format == "Port") {
            c.setLineDash([5, 5]);
        }
        else {
            c.setLineDash([]);
        }

        c.beginPath();
        c.moveTo(parseFloat(detail_route[0][0] - modify_x) * 2, parseFloat(detail_route[0][1] - modify_y) * 2);
        var center_x = parseFloat(detail_route[0][0] - modify_x) * 2;
        var center_y = parseFloat(detail_route[0][1] - modify_y) * 2;
        for (var i = 1; i < detail_route.length; i++) {
            let next_x = parseFloat(detail_route[i][0] - modify_x) * 2;
            let next_y = parseFloat(detail_route[i][1] - modify_y) * 2;
            c.lineTo(next_x, next_y);
            center_x = center_x + next_x;
            center_y = center_y + next_y;
        }
        center_x = center_x / (detail_route.length);
        center_y = center_y / (detail_route.length);
        c.lineTo(parseFloat(detail_route[0][0] - modify_x) * 2, parseFloat(detail_route[0][1] - modify_y) * 2);
        if (target.Format == "Boundary") {
            c.strokeStyle = "8543E0";
            c.fillStyle = "rgba(131,175,155, 0.3)"
            c.fill();

        }
        else if (target.Format == "Port") {
            c.strokeStyle = "black";
            c.fillStyle = "rgba(252,157,154, 0.3)"
            c.fill();

        }

        c.stroke();
        if (target.Format == "Boundary") {
            c.font = '14pt Calibri';
            c.textAlign = 'center';
            c.fillStyle = "red";
            c.fillText(target.Module_name, center_x, center_y);
        }
    }
    // console.log("Hello!" + m_pkg);
    /**
     * target: load json from computer
     * @param {json local path} path 
     */
    function extract_json_path(path) {
        $.ajax({
            type: "GET",
            dataType: "json",
            url: path,
            result: {},
            success: function (result) {
                test_data = result;
                test0 = result;
                process_data(test_data);
            }
        });
    };
    function process_data(test_data) {
        var temp_module_data = test_data.Modules;
        var temp_area_data = test_data.Area;
        var temp_rule_data = test_data.Rules;

        tot = temp_module_data;

        for (var i = 0; i < temp_area_data.length; i++) {
            if (temp_area_data[i][0] < modify_x) {
                modify_x = temp_area_data[i][0];
            }
            if (temp_area_data[i][1] < modify_y) {
                modify_y = temp_area_data[i][1];
            }
            if (temp_area_data[i][0] > max_x) {
                max_x = temp_area_data[i][0];
            }
            if (temp_area_data[i][1] > max_y) {
                max_y = temp_area_data[i][1];
            }
        }
        resize_canvas(modify_x, max_x, modify_y, max_y);

        // console.log("Module data:" + temp_module_data);
        console.log("Rules data:" + temp_rule_data);
        for (var i = 0; i < temp_module_data.length; i++) {
            var current_position = {};
            current_position.Location = temp_module_data[i].Boundary;
            current_position.Format = "Boundary";
            current_position.Type = "GATE";
            current_position.Module_name = temp_module_data[i].Module;
            draw_canvas2(current_position);
            for (var j = 0; j < temp_module_data[i].Ports.length; j++) {
                temp_module_data[i].Ports[j].Format = "Port";
                // console.log(temp_module_data[i].Ports[j]);
                draw_canvas2(temp_module_data[i].Ports[j]);
            }
        }
    }
    var json_pth = "./data/" + VLSI + ".json";
    var connect_pth = "./data/" + VLSI + "connect.json";
    extract_json_path(json_pth);
    // alert(test0);
    // extract_connect_json_path(connect_pth);
}

// function draw_canvas4(VLSI) {
//     var connect_pth = "./data/" + VLSI + "connect.json";
//     extract_connect_json_path(connect_pth, VLSI);

// }


function extract_connect_json_path(VLSI) {
    $.ajax({
        type: "GET",
        dataType: "json",
        url: "./data/" + VLSI + "connect.json",
        connect_result: {},
        success: function (connect_result) {
            con_data = connect_result;
            // process_connect_data(con_data);
            $.ajax({
                type: "GET",
                dataType: "json",
                url: "./data/" + VLSI + ".json",
                result: {},
                success: function (result) {
                    // result 存储的是
                    test_data = result;
                    $("#tg").html(""); // 清除存储tag的所有内容
                    // alert(con_data.length);
                    console.log(con_data);
                    // radio input 
                    var e = document.getElementById("tg");
                    // var div = document.createElement("div");
                    // function output(i) {
                    //     alert("HA");
                    // }

                    for (var i = 0; i < con_data.length; i++) {
                        var button = document.createElement("input");
                        button.setAttribute("type", "checkbox");
                        // button.setAttribute("value", 10);
                        button.setAttribute("value", (i + 1));
                        button.setAttribute("id", "box" + i);
                        // button.innerHTML = "Link " + (i + 1);
                        // button.setAttribute("class", class);
                        // button.style.width = "12%";
                        // button.setAttribute("checked", output(i));
                        e.appendChild(button);
                    }
                    // document.getElementById("form").appendChild(div);
                }
            });
        }
    });
}

/**
 * 处理connect的数据
 */
function process_connect_data(connect_data) {
    for (var i = 0; i < connect_data.length; i++) {
        // console.log(connect_data[i]);
        var current_connect = connect_data[i];
    }
}
// process_connect_data()

function get_package_name() {
    var t = $("#packageNameInput").val();
    var pkg = $('#package').val();
    pkg = pkg + "-" + t;
    m_pkg = pkg;
    document.getElementById("demo").innerHTML = "Current package name:" + pkg;
    draw_canvas3(m_pkg);
}

$(document).ready(function () {
    $('#packageNameInput').keydown(function (e) {
        var $s = $('#packageNameInput').val();
        var $p = $('#package').val();
        if (e.keyCode == 13) {
            // alert($p + "-" + $s);
            draw_canvas3($p + "-" + $s);
            extract_connect_json_path($p + "-" + $s);
            // draw_canvas4($p + "-" + $s);
            document.getElementById("demo").innerHTML = "Current package name:" + $p + "-" + $s;
        }
    });
});



