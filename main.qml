import QtQuick.Controls
import QtCharts


ApplicationWindow {
	width: 640
	height: 640
	visible: true

	ChartView {
		id: pie
		x: 164
		y: 154
		width: 300
		height: 300
		PieSeries {
			name: "PieSeries"
			PieSlice {
				value: 13.5
				label: "Slice"
			}

			PieSlice {
				value: 10.9
				label: "Slice2"
			}

			PieSlice {
				value: 8.6
				label: "Slice3"
			}
		}
	}
}