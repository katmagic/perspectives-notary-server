const REPORT_URI = "http://localhost/posthere";

/*
   cert.commonName
   cert.organization
   cert.organizationalUnit
   cert.serialNumber
   cert.sha1Fingerprint
   cert.md5Fingerprint
   cert.validity.notBeforeLocalDay
   cert.validity.notAfterLocalDay
   cert.issuerCommonName
   cert.issuerOrganization
   cert.issuerOrganizationUnit
*/


var report = function () {

    function get_ip_str(hostname) {
        var ips    = get_ips(hostname);
        var ip_str = "";

        if (ips.length <= 0 ) {
            return ip_str;
        }

        ip_str = ips[0];

        if (ips.length == 1) {
            return ip_str;
        }

        for (var i = 1; i < ips.length; i++) {
            ip_str= ip_str + "," + ips[i];
        }

        return ip_str;
    }

    function post_attack_data(attack_data) {
        var req; // XMLHttpRequest
        var body;

        body = body + "uri="   + attack_data.uri;
        body = body + "&cert=" + attack_data.cert;

        req = new XMLHttpRequest();
        req.open("POST", REPORT_URI);
        req.setRequestHeader("Content-Type",
                             "application/x-www-form-urlencoded");

        req.send(body);
    }

    function report_attack(b, cert) {
        /* Grep the source figure out what data I can get and copy the xul */
        var attack_data;
        var ret;

        attack_data      = {};
        attack_data.uri  = b.currentURI.spec;
        attack_data.cert = cert;
        attack_data.host = b.currentURI.host;
        attack_data.ips  = get_ip_str(attack_data.host);
        ret              = { do_post : false };

        window.openDialog("chrome://perspectives/content/report.xul", "", "",
                          attack_data, ret).focus();

        if (ret.do_post) {
            post_attack_data(attack_data);
        }
    }

    obj               = {};
    obj.report_attack = report_attack;

    return obj;
}();

