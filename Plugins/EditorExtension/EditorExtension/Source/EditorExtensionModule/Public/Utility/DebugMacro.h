#ifdef EXCLUDE_THIS_FILE
TO_STRING_PREPROCESSING(aX) #aX=
TO_STRING(aX) TO_STRING_PREPROCESSING(aX)=
EDITOR_LOG(aLogMessage, ...) UE_LOG(LogTemp, Log, TEXT(aLogMessage), ##__VA_ARGS__)=
EDITOR_LOG_WARNING(aLogMessage, ...) UE_LOG(LogTemp, Warning, TEXT(aLogMessage), ##__VA_ARGS__)=
EDITOR_LOG_ERROR(aLogMessage, ...) UE_LOG(LogTemp, Error, TEXT(aLogMessage), ##__VA_ARGS__)=
EDITOR_LOG_FATAL(aLogMessage, ...) UE_LOG(LogTemp, Fatal, TEXT(aLogMessage), ##__VA_ARGS__)=
EDITOR_DIALOGUE_ATTENTION(aLogMessage) {FMessageDialog::Open(EAppMsgCategory::Error, EAppMsgType::Ok, FText::FromString(TEXT("[ DETAIL ]" "\n\n" "Reason:" "\n" aLogMessage "\n\n" "Source:" "\n" __FILE__ "\n\n" "Location:" "\n" TO_STRING(__LINE__) " Line" " in " __FUNCTION__)), FText::FromString(TEXT("Attention")));}=
#endif