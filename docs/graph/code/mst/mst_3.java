import java.util.Arrays;
import java.util.Scanner;

class Edge {
    int u;
    int v;
    int w;

    Edge(int u, int v, int w) {
        this.u = u;
        this.v = v;
        this.w = w;
    }
}

public class Main {
    static int[] parent = new int[1010];  // define parent
    static int m, n, k;  // n is the number of vertices, m is the number of edges, k is the number of marshmallows needed

    static Edge[] edges = new Edge[10010];
    static int l;

    static void addEdge(int u, int v, int w) {
        edges[++l] = new Edge(u, v, w);
    }

    // standard DSU
    static int findroot(int x) {
        if (parent[x] != x) {
            parent[x] = findroot(parent[x]);
        }
        return parent[x];
    }

    static void Merge(int x, int y) {
        x = findroot(x);
        y = findroot(y);
        parent[x] = y;
    }

    static boolean cmp(Edge A, Edge B) {
        return A.w < B.w;
    }

    // Kruskal's algorithm
    static void kruskal() {
        int tot = 0;  // number of edges chosen
        int ans = 0;  // total cost

        for (int i = 1; i <= m; i++) {
            int xr = findroot(edges[i].u);
            int yr = findroot(edges[i].v);
            if (xr != yr) {   // if the roots differ
                Merge(xr, yr); // merge
                tot++; // one more edge
                ans += edges[i].w; // add the cost
                if (tot == n - k) {  // check whether the edge count gives k marshmallows
                    System.out.println(ans);
                    return;
                }
            }
        }
        System.out.println("No Answer");  // cannot be connected
    }

    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        n = scanner.nextInt();
        m = scanner.nextInt();
        k = scanner.nextInt();

        if (n == k) { // handle the edge case
            System.out.println("0");
            return;
        }

        // initialize
        for (int i = 1; i <= n; i++) {
            parent[i] = i;
        }
        for (int i = 1; i <= m; i++) {
            int u = scanner.nextInt();
            int v = scanner.nextInt();
            int w = scanner.nextInt();
            addEdge(u, v, w);  // add edge
        }
        Arrays.sort(edges, 1, m + 1, (a, b) -> Integer.compare(a.w, b.w));  // sort by edge weight first
        kruskal();
        scanner.close();
    }
}
