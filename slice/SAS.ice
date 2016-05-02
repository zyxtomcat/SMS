

module SAS {

	/*********************************************************************************************
	//Send downstream SMS request
	{
		"sim" : "",
		"content" : ""
	}

	//Send downstream SMS response 
	{
		"result":
		"msg":""
	}

	//Query upstream SMS request
	{
		"sim" : "",
		"begin_time" : "",				//yyyy-MM-dd hh:mm:ss
		"end_time" : ""
	}

	//Query upstream SMS response
	{
		"result":,
		"msg" : "",
		"data" :{
					"sim" : "",
					"sms": 	[
								{
								"content" : "",
								"time" : ""
								},
									...
							]
				}
	}

	*********************************************************************************************/
	
	interface SASSession {
		//Send downsteam SMS
		void SendSMS(string request, out string response);

		//Query upstream SMS
		void QuerySMS(string request, out string response);
	};
};
