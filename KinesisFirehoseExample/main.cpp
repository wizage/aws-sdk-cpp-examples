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

    Aws::String region = "us-west-2";
    Aws::String jsonData = "This is awesome.";
    Aws::Utils::ByteBuffer buffer = Aws::Utils::ByteBuffer(reinterpret_cast<const unsigned char*>(jsonData.data()), jsonData.size());
    Aws::String base64data = Aws::Utils::HashingUtils::Base64Encode(buffer);

    Aws::Client::ClientConfiguration clientConfig;
    clientConfig.region = region;

    Aws::Firehose::FirehoseClient firehose_client = { clientConfig };

    Aws::Firehose::Model::PutRecordRequest requestSmall;

    Aws::Utils::Json::JsonValue jsonStuff;
    jsonStuff = jsonStuff.WithString("Data", base64data);


    Aws::Firehose::Model::Record t = Aws::Firehose::Model::Record();

    t = jsonStuff;

    requestSmall.SetDeliveryStreamName("testFirehose");
    requestSmall.SetRecord(t);

    std::cout << requestSmall.SerializePayload() << std::endl;


        /*
        Aws::Firehose::Model::PutRecordBatchRequest::PutRecordBatchRequest requestStuff = Aws::Firehose::Model::PutRecordBatchRequest::PutRecordBatchRequest();
        std::cout << "Record Batch Request" << std::endl;

        std::cout << jsonStuff.GetInteger("test") << std::endl;

        std::cout << "Json" << std::endl;

        requestStuff.SetDeliveryStreamName("testFirehose");
        requestStuff.AddRecords(t);
        requestStuff.AddRecords(t);
        requestStuff.AddRecords(t);

        std::cout << "Batch created" << std::endl;
        */
    
    auto outcome_push = firehose_client.PutRecord(requestSmall);

    std::cout << "Sent" << std::endl;

    if (outcome_push.IsSuccess()){
        std::cout << "We put stuff in there" << std::endl;
    } else
    {
        std::cout << "Error log: " << outcome_push.GetError().GetExceptionName() << " - " << outcome_push.GetError().GetMessage() << std::endl;
    }

      // make your SDK calls here.
   }
   Aws::ShutdownAPI(options);
   return 0;
}