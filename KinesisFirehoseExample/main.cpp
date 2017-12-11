#include <aws/core/Aws.h>
#include <aws/core/utils/Outcome.h>
#include <aws/firehose/FirehoseClient.h>
#include <aws/firehose/FirehoseErrors.h>
#include <aws/firehose/model/Record.h>
#include <aws/firehose/model/PutRecordRequest.h>
#include <aws/firehose/model/PutRecordBatchRequest.h>
#include <aws/firehose/model/PutRecordBatchResult.h>
#include <aws/core/utils/HashingUtils.h>
int main()
{
   Aws::SDKOptions options;
   Aws::InitAPI(options);
   {
        /**
         * This is the data you will be sending in. This will need to be base64 
         * encoded to be translated correctly when you send it to the firehose.
         * This is defined in the api here:
         * http://docs.aws.amazon.com/firehose/latest/APIReference/API_Record.html
         */
        Aws::String jsonData = "This is awesome.";
        Aws::Utils::ByteBuffer buffer = Aws::Utils::ByteBuffer(reinterpret_cast<const unsigned char*>(jsonData.data()), jsonData.size());
        Aws::String base64data = Aws::Utils::HashingUtils::Base64Encode(buffer);
        
        /**
         * This setups up your client that you will be using to communicate with
         * the cloud. You can define your region, max connections and much more
         * defined here:
         * https://sdk.amazonaws.com/cpp/api/LATEST/struct_aws_1_1_client_1_1_client_configuration.html
         */
        Aws::String region = "us-west-2";
        Aws::Client::ClientConfiguration clientConfig;
        clientConfig.region = region;

        /**
         * Setup the firehose client using the client we defined above. You also
         * can pass in AWS Credentials if you want.
         */
        Aws::Firehose::FirehoseClient firehose_client = { clientConfig };
        
        
        Aws::Utils::Json::JsonValue jsonObject;
        jsonObject = jsonObject.WithString("Data", base64data);

        Aws::Firehose::Model::Record newRecord = jsonObject;
        
        Aws::Firehose::Model::PutRecordRequest recordRequest;
        recordRequest.SetDeliveryStreamName("testFirehose");
        recordRequest.SetRecord(newRecord);

    
        auto outcome_push = firehose_client.PutRecord(recordRequest);

        if (outcome_push.IsSuccess()){
            std::cout << "Successfully pushed data to the firehose" << std::endl;
        } else
        {
            std::cout << "Error log: " << outcome_push.GetError().GetExceptionName() << " - " << outcome_push.GetError().GetMessage() << std::endl;
        }
   }
   Aws::ShutdownAPI(options);
   return 0;
}