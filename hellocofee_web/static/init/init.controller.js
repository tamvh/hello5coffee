/* global theApp, ZaloPay */

(function () {
    'use strict';

    theApp.controller('InitController', InitController);

    InitController.$inject = ['$scope', 'InitService', '$rootScope', '$cookies', '$uibModal', '$timeout', '$location', 'PopupService'];
    function InitController($scope, InitService, $rootScope, $cookies, $uibModal, $timeout, $location, PopupService) {
        $rootScope.dt_items = [];
        $rootScope.l_categories = [];
        var img_host = "";
        $scope.styleloading = "margin-top:" + ($(window).height() / 2-30) + "px;";
        function get_params() {
            var cur_url = window.location.href;
            if (cur_url.split('?').length === 2) {
                var params = cur_url.split('?')[1];
                if (params.split('=').length === 2) {
                    var dt = params.split('=')[1];
                    var json_obj = JSON.parse(decodeURI(dt));
                    $rootScope.customer_location = json_obj.customer_location;
                }
            }
        }

        $scope.getProdInCategory = function (cate) {
            console.log("cate: " + JSON.stringify(cate));
            var count_item_in_cate = 0;
            $rootScope.l_pro.splice(0, $rootScope.l_pro.length);
            var cate_name = cate.category_name;
            var cate_value = cate.category_value;
            var cate_id = cate.category_id;
            console.log('cate list: ' + JSON.stringify($rootScope.l_categories));
            for (var j in $rootScope.l_categories) {
                console.log('cate_id: ' + $rootScope.l_categories[j].category_id);
                if (cate_id === $rootScope.l_categories[j].category_id) {
                    $rootScope.l_categories[j].category_color = "#00A2E6";
                    $scope.current_category = $rootScope.l_categories[j].category_name;
                } else {
                    $rootScope.l_categories[j].category_color = "#000000";
                }
            }
            if (cate_name === "Tất cả") {

                for (var i in $rootScope.dt_items) {
                    if ($rootScope.dt_items[i].status === 1) {
                        count_item_in_cate = count_item_in_cate + 1;
                        $rootScope.l_pro.push($rootScope.dt_items[i]);
                    }
                }
                $rootScope.total_item_in_category = count_item_in_cate;
                document.getElementById("mySidenav").style.width = "0";
                return;
            }


            for (var i in $rootScope.dt_items) {
                console.log("cast_mark: " + $rootScope.dt_items[i].cate_mask);
                if ($scope.checkMask($rootScope.dt_items[i].cate_mask, cate_value)) {
                    if ($rootScope.dt_items[i].status === 1) {
                        count_item_in_cate = count_item_in_cate + 1;
                        $rootScope.l_pro.push($rootScope.dt_items[i]);
                    }
                }
            }
            document.getElementById("mySidenav").style.width = "0";
            $rootScope.total_item_in_category = count_item_in_cate;
        };

        $scope.checkMask = function (mask, value) {
            var hiMask = mask / 4294967296;
            var loMask = mask % 4294967296;
            var hiValue = value / 4294967296;
            var lovalue = value % 4294967296;
            if (((hiMask & hiValue) !== 0) || ((loMask & lovalue) !== 0))
                return true;
            return false;
        };

        $scope.gettotal_money = function () {
            var _soluong = 0;
            var _amount = 0;
            var _price = 0;
            var _total_amout = 0;

            for (var j in $rootScope.foodItems) {
                _soluong = $rootScope.foodItems[j].quantity;
                _price = $rootScope.foodItems[j].price;
                _amount = _price * _soluong;
                _total_amout = _total_amout + _amount;
            }
            $rootScope.totalmoney = _total_amout;
        };

        function xoa_dau(str) {
            str = str.replace(/à|á|ạ|ả|ã|â|ầ|ấ|ậ|ẩ|ẫ|ă|ằ|ắ|ặ|ẳ|ẵ/g, "a");
            str = str.replace(/è|é|ẹ|ẻ|ẽ|ê|ề|ế|ệ|ể|ễ/g, "e");
            str = str.replace(/ì|í|ị|ỉ|ĩ/g, "i");
            str = str.replace(/ò|ó|ọ|ỏ|õ|ô|ồ|ố|ộ|ổ|ỗ|ơ|ờ|ớ|ợ|ở|ỡ/g, "o");
            str = str.replace(/ù|ú|ụ|ủ|ũ|ư|ừ|ứ|ự|ử|ữ/g, "u");
            str = str.replace(/ỳ|ý|ỵ|ỷ|ỹ/g, "y");
            str = str.replace(/đ/g, "d");
            str = str.replace(/À|Á|Ạ|Ả|Ã|Â|Ầ|Ấ|Ậ|Ẩ|Ẫ|Ă|Ằ|Ắ|Ặ|Ẳ|Ẵ/g, "A");
            str = str.replace(/È|É|Ẹ|Ẻ|Ẽ|Ê|Ề|Ế|Ệ|Ể|Ễ/g, "E");
            str = str.replace(/Ì|Í|Ị|Ỉ|Ĩ/g, "I");
            str = str.replace(/Ò|Ó|Ọ|Ỏ|Õ|Ô|Ồ|Ố|Ộ|Ổ|Ỗ|Ơ|Ờ|Ớ|Ợ|Ở|Ỡ/g, "O");
            str = str.replace(/Ù|Ú|Ụ|Ủ|Ũ|Ư|Ừ|Ứ|Ự|Ử|Ữ/g, "U");
            str = str.replace(/Ỳ|Ý|Ỵ|Ỷ|Ỹ/g, "Y");
            str = str.replace(/Đ/g, "D");
            return str;
        }

        $scope.getListProduct = function () {
            $scope.showloding = true;
            get_params();
            $rootScope.l_categories = [];
            $rootScope.l_pro = [];
            InitService.getListProduct()
                    .then(function (response) {
                        if (response.err === 0) {
                            img_host = response.dt.img_host;
                            for (var i in response.dt.categories) {
                                if (response.dt.categories[i].status === 0 &&
                                        response.dt.categories[i].category_name === 'Tất cả') {
                                    response.dt.categories[i].category_color = "#00A2E6";
                                    response.dt.categories[i].icon = "img/item_all.svg";
                                    $rootScope.l_categories.push(response.dt.categories[i]);
                                }
                                if (response.dt.categories[i].status === 1) {
                                    response.dt.categories[i].category_color = "#000000";
                                    response.dt.categories[i].icon = "img/menu_item.svg";
                                    $rootScope.l_categories.push(response.dt.categories[i]);
                                }

                            }
                            $rootScope.dt_items = response.dt.items;
                            if ($rootScope.foodItems.length > 0) {
                                for (var i in $rootScope.dt_items) {
                                    if ($rootScope.dt_items[i].status === 1) {
                                        $rootScope.dt_items[i].name_view = $rootScope.dt_items[i].item_name;
                                        $rootScope.dt_items[i].name_view_noaccent = xoa_dau($rootScope.dt_items[i].item_name);
                                        if (checkExistImgUrl($rootScope.dt_items[i].img_path)) {
                                            $rootScope.dt_items[i].img_path = img_host + $rootScope.dt_items[i].img_path;
                                        } else {
                                            $rootScope.dt_items[i].img_path = "img/noimg.png";
                                        }

                                        $rootScope.dt_items[i].img_checked = "img/checked.png";

                                        $rootScope.dt_items[i].img = $rootScope.dt_items[i].img_path;

                                        $rootScope.dt_items[i].quantity = 0;
                                        $rootScope.dt_items[i].show_quantity = false;
                                        $rootScope.dt_items[i].bgcolor = "white";
                                        for (var j in $rootScope.foodItems) {
                                            if ($rootScope.foodItems[j].index === $rootScope.dt_items[i].item_id) {
                                                $rootScope.dt_items[i].img = "img/checked.png";
                                                $rootScope.dt_items[i].quantity = $rootScope.foodItems[j].quantity;
                                                if ($rootScope.dt_items[i].quantity > 0) {
                                                    $rootScope.dt_items[i].show_quantity = true;
                                                } else {
                                                    $rootScope.dt_items[i].show_quantity = false;
                                                }
                                                $rootScope.dt_items[i].showaction = true;
                                                $rootScope.dt_items[i].bgcolor = "#E0E0E0";
                                                break;
                                            }
                                        }
                                        $rootScope.l_pro.push($rootScope.dt_items[i]);
                                    }

                                }
                            } else {
                                for (var i in $rootScope.dt_items) {
                                    if ($rootScope.dt_items[i].status === 1) {
                                        $rootScope.dt_items[i].bgcolor = "white";
                                        $rootScope.dt_items[i].name_view = $rootScope.dt_items[i].item_name;
                                        $rootScope.dt_items[i].name_view_noaccent = xoa_dau($rootScope.dt_items[i].item_name);
                                        $rootScope.dt_items[i].quantity = 0;
                                        if (checkExistImgUrl($rootScope.dt_items[i].img_path)) {
                                            $rootScope.dt_items[i].img_path = img_host + $rootScope.dt_items[i].img_path;
                                        } else {
                                            $rootScope.dt_items[i].img_path = "img/noimg.png";
                                        }
                                        $rootScope.dt_items[i].showaction = false;
                                        $rootScope.dt_items[i].img_checked = "img/checked.png";
                                        $rootScope.dt_items[i].img = $rootScope.dt_items[i].img_path;
                                        if ($rootScope.dt_items[i].quantity > 0) {
                                            $rootScope.dt_items[i].show_quantity = true;
                                        } else {
                                            $rootScope.dt_items[i].show_quantity = false;
                                        }
                                        $rootScope.l_pro.push($rootScope.dt_items[i]);
                                    }
                                }
                            }

                        } else {
                            console.log("error getListProduct");
                        }
                        $rootScope.total_item_in_category = $rootScope.dt_items.length;
                    });
            $scope.gettotal_money();
            $scope.showloding = false;
            $location.path("/");
        };

        function checkExistImgUrl(img_url) {
            var local_img_url = img_url;
            if (local_img_url.search(".jpg") >= 0 || local_img_url.search(".png") >= 0 || local_img_url.search(".jepg") >= 0) {
                return true;
            }
            return false;
        }

        $scope.getListProduct();
    }
})();