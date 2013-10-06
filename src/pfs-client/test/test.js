var pfs = require('../index'),
    should = require('should'),
    fs = require('fs'),
    assert = require("assert");

module.exports = {
    setUp: function (callback) {
        var testSelf = this;
        should.exist(pfs.createClient);
        this.client = pfs.createClient();
        should.exist(this.client);

        this.client.on('connect', function () {
            testSelf.connected = true;
        });
        this.client.on('error', function (e) {
            console.log('Error in client:', e);
            callback(e);
        });

        this.client.on('end', function () {
            console.log('client ended.');
        });

        should.exist(this.client.connect);

        this.client.connect(function (err) {
            throw err;
        });
        callback();
    },

    tearDown: function (callback) {
        should.exist(this.client.end);
        if (this.connected) {
            this.client.end(function (err) {
                console.log('Error in tearDown:', err);
                callback(err);
            });
        }
        callback();
    },

    testPing: function (test) {
        should.exist(this.client.ping);
        this.client.ping(function (err, result) {
                test.equals(err, null, 'No error should be thrown.' + err);
                test.equals(result, 0, 'Ping result must be 0');
                test.done();
            }
        );
    },

    testDetectFaces : function(test) {
        should.exist(this.client.detectFaces);
        //test with real image
        var pfsClient = this.client;
        var tester = test;
        fs.readFile('girl.jpg', function(fsErr, data){
            if (fsErr) {
                console.log('error in reading test image file.\n');
                tester.done();
            } else {
                tester.ok(data);
                tester.ok(data.length > 0);
                pfsClient.detectFaces(data, 199, 300, function(err, faces){
                    should.not.exist(err);
                    should.exist(faces);
                    console.log(faces);
                    tester.ok(faces.length == 1, 'One face must be detected.');
                    tester.done();
                });
            }
        });
    }

}
