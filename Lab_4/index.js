const {TwitterApi} = require('twitter-api-v2');

exports.handler = async (event) => {
    const data = JSON.parse(event.body);

    const T = new TwitterApi({
	"appKey": "**********APPKEYGOESHERE**********",
	"appSecret": "**********APPSECRETGOESHERE**********",
	"accessToken": "**********ACCESSTOKEN**********",
	"accessSecret": "**********ACCESSSECRET**********",
    });

    await T.v2.tweet(data.text);

    const response = {
        statusCode: 200,
        body: JSON.stringify('Returning from Lambda'),
    };
    return response;
};

