/* global theApp */
(function () {
    'use strict';
    theApp.factory('InitService', InitService);

    InitService.$inject = ['$http', 'API_URL', 'ZALOPAY_URL', 'MERCHANT_CODE'];
    function InitService($http, API_URL, ZALOPAY_URL, MERCHANT_CODE) {
        var service = {};
        var url = API_URL + "/item/"; 
        var mc = MERCHANT_CODE;
        
        service.getListProduct = getListProduct;
        return service;

        function getListProduct() {
            var cmd = "getlist";
            var dtJSON = {merchant_code: mc};
            var dt = JSON.stringify(dtJSON);
            var data = $.param({
                cm: cmd,
                dt: dt
            });           
            return $http.post(url, data).then(handleSuccess, handleError('Error listing item'));   
        }               

        function handleSuccess(res) {
            return res.data;
        }

        function handleError(error) {            
            return function () {
                return { err: -2, msg: error };
            };
        }       
    }    
})();
