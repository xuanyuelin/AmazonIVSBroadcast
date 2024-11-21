// swift-tools-version: 6.0

import PackageDescription

let package = Package(
    name: "AmazonIVSBroadcast",
    products: [
        // Products define the executables and libraries a package produces, making them visible to other packages.
        .library(
            name: "AmazonIVSBroadcast",
            targets: ["AmazonIVSBroadcast"]
		),
    ],
    targets: [
		.binaryTarget(
			name: "AmazonIVSBroadcast",
			path: "./AmazonIVSBroadcast/AmazonIVSBroadcast.xcframework"
		)
    ]
)
