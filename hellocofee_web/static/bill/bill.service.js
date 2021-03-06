/* global theApp, sjcl */
(function () {
    'use strict';
    theApp.factory('BillService', BillService);

    BillService.$inject = ['$rootScope', '$http', '$q', 'API_URL', 'ZALOPAY_URL'];
    function BillService($rootScope, $http, $q, API_URL, ZALOPAY_URL) {
        var service = {};
        var url = API_URL + "/invoice/";
        var url_zalopay = ZALOPAY_URL;
        var p_method = 1; // zalopay
        var appTitle = "";
        var machine_name = "W-VPOS";
        var key = "7VShsAFE3S4pS3lijpCkIxCDpzi7ljdS";

        service.createQRCode = createQRCode;
        service.getListProduct = getListProduct;
        service.doGetPmsid = doGetPmsid;
        service.doPayZalo = doPayZalo;
        return service;

        function doPayZalo(merchant_code, uuid, sesId, biId, amount, items, customer_name, phone_no, bill_note) {
            var cmd = "create";
            appTitle = "VI TRI: " + $rootScope.customer_location;
            var dtJSONNote = {
                customer_name: customer_name,
                phone_no: phone_no,
                bill_note: bill_note,
                location: $rootScope.customer_location
            };
            var dtStringNote = JSON.stringify(dtJSONNote);
            
            var dtJSON = {
                merchant_code: merchant_code,
                foodsorder_id: biId,
                machine_name: machine_name,
                description: appTitle,
                appuser: merchant_code,
                amount: amount,
                devid: uuid,
                apptype: 7,
                items: items,
                payment_method: p_method,
                note: dtStringNote
            };
            
            console.log('dtJSON: ' + JSON.stringify(dtJSON));
            
            var dt = JSON.stringify(dtJSON);
            var token = HMAC_SHA256_MAC(key, dt + sesId);
            var data = $.param({
                cm: cmd,
                tk: token,
                sid: sesId,
                dt: dt
            });
            return $http.post(url, data).then(handleSuccess, handleError('Error doPayZalo'));
        }
        
        function doGetPmsid(merchant_code, deviceId, billId) {
            var cmd = "get_session";
            var dtJSON = {
                merchant_code: merchant_code,
                food_order: billId,
                devid: deviceId
            };
            var dt = JSON.stringify(dtJSON);
            var data = $.param({
                cm: cmd,
                dt: dt
            });
            return $http.post(url, data).then(handleSuccess, handleError('Error get session'));
        }

        function getListProduct(merchant_code) {
            var cmd = "getlist";
            var dtJSON = {merchant_code: merchant_code};
            var dt = JSON.stringify(dtJSON);
            var data = $.param({
                cm: cmd,
                dt: dt
            });
            return $http.post(url, data).then(handleSuccess, handleError('Error listing item'));
        }

        function createQRCode(appid, zptranstoken) {
            var param = "?appid=" + appid + "&zptranstoken=" + zptranstoken;
            return $http.get(url_zalopay + param).then(handleSuccess, handleError('Error when create QRCode'));
        }

        function handleSuccess(res) {
            return res.data;
        }

        function handleError(error) {
            return function () {
                return {err: -2, msg: error};
            };
        }
    }
})();
