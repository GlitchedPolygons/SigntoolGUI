#ifndef CONSTANTS_H
#define CONSTANTS_H

struct Constants
{
    struct Settings
    {
        static inline const char* windowWidth = "WindowWidth";
        static inline const char* windowHeight = "WindowHeight";
        static inline const char* pfxFile = "PfxFile";
        static inline const char* hashAlgo = "HashingAlgorithm";
        static inline const char* timestampHashAlgo = "TimestampHashingAlgorithm";
        static inline const char* timestampServerUrl = "TimestampServerUrl";

        static inline const char* saveWindowSizeOnQuit = "SaveWindowSizeOnQuit";
        static inline const char* saveHashAlgoOnQuit = "SaveHashingAlgorithmOnQuit";
        static inline const char* saveTimestampHashAlgoOnQuit = "SaveTimestampHashingAlgorithmOnQuit";
        static inline const char* savePfxFilePathOnQuit = "SavePfxFilePathOnQuit";
        static inline const char* saveTimestampServerUrlOnQuit = "SaveTimestampServerUrlOnQuit";


        struct DefaultValues
        {
            static inline bool saveWindowSizeOnQuit = false;
            static inline bool saveHashAlgoOnQuit = true;
            static inline bool saveTimestampHashAlgoOnQuit = true;
            static inline bool savePfxFilePathOnQuit = true;
            static inline bool saveTimestampServerUrlOnQuit = true;

            static inline const char* pfxFile = "";
            static inline int hashAlgo = 2;
            static inline int timestampHashAlgo = 2;
            static inline const char* timestampServerUrl = "http://timestamp.digicert.com";
        };
    };

    static inline const char* appName = "SigntoolGUI";
    static inline const char* appVersion = "1.1.0";
    static inline const char* orgName = "Glitched Polygons GmbH";
    static inline const char* orgDomain = "glitchedpolygons.com";

};

#endif // CONSTANTS_H
