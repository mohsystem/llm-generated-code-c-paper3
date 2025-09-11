// Task108.proto
service Task108 {
    rpc ManipulateObject(ManipulateRequest) returns (ManipulateReply) {}
}

message ManipulateRequest {
    string command = 1;
}

message ManipulateReply {
    string result = 1;
}